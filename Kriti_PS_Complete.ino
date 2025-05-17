#include <IRremote.h>
#include <Servo.h>

// IR receiver object on pin 7
IRrecv IR(7);

// Servo object
Servo speedometerServo;

#define BRAKE_PIN   8  // Output pin to brake mechanism (if still needed)

// Define input pins 
const int bit0Pin = 2;  // Least significant bit (rightmost)
const int bit1Pin = 3;
const int bit2Pin = 4;
const int bit3Pin = 5;  // Most significant bit (leftmost)

int servoAngle = 180; // Default servo angle
bool brakeApplied = false; // Flag to track brake state

// IR code that activates the brake
const unsigned long BRAKE_CODE = 0xE619FF00;
const unsigned long NO_BRAKE_CODE = 0xBA45FF00;

void setup() {
  Serial.begin(9600);

  // Initialize IR reception
  IR.enableIRIn();

  // Set brake pin as output
  pinMode(BRAKE_PIN, OUTPUT);
  digitalWrite(BRAKE_PIN, LOW); // Default brake off

  // Configure input pins with internal pull-up resistors
  pinMode(bit0Pin, INPUT);
  pinMode(bit1Pin, INPUT);
  pinMode(bit2Pin, INPUT);
  pinMode(bit3Pin, INPUT);

  // Attach servo to pin 9
  speedometerServo.attach(9);
  speedometerServo.write(180);
}

void loop() {
  // IR decoding
  if (IR.decode()) {
    Serial.print("IR Code: 0x");
    Serial.println(IR.decodedIRData.decodedRawData, HEX);

    if (IR.decodedIRData.decodedRawData == BRAKE_CODE) {
      Serial.println("BRAKE CODE RECEIVED -> Activating brake");
      digitalWrite(BRAKE_PIN, HIGH);
      brakeApplied = true; // Set brake flag
    } else if (IR.decodedIRData.decodedRawData == NO_BRAKE_CODE) {
      Serial.println("NO BRAKE CODE RECEIVED -> Releasing brake");
      digitalWrite(BRAKE_PIN, LOW);
      brakeApplied = false; // Clear brake flag
    }

    IR.resume(); // Ready for next IR signal
  }

  // If brake is applied, force speedometer to 180 degrees
  if (brakeApplied) {
    speedometerServo.write(180);
    return; // Skip further execution to ensure no speed is set
  }

  // Read all digital inputs (inverted because we're using pull-ups)
  int b0 = digitalRead(bit0Pin);
  int b1 = digitalRead(bit1Pin);
  int b2 = digitalRead(bit2Pin);
  int b3 = digitalRead(bit3Pin);

  // Combine bits into a single value
  int inputValue = b0 + (b1 << 1) + (b2 << 2) + (b3 << 3);

  // Determine servo angle based on input combination
  switch (inputValue) {
    case 0b0000:  // 0000 - Stop
      servoAngle = 180;
      break;
    case 0b0001:  // 0001 - Speed 1
      servoAngle = 135;
      break;
    case 0b0011:  // 0011 - Speed 2
      servoAngle = 90;
      break;
    case 0b0111:  // 0111 - Speed 3
      servoAngle = 45;
      break;
    case 0b1111:  // 1111 - Max Speed
      servoAngle = 0;
      break;
    default:      // Invalid combination (use previous state)
      return;
  }

  // Move servo to selected position
  speedometerServo.write(servoAngle);

  delay(50); // Small delay for stability
}
