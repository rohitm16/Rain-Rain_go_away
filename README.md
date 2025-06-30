# 🌧️ Rain-Rain-Go-Away: KRITI'25 2nd Place Solution

## 🏆 Project Overview

**Rain-Rain-Go-Away** was our team's innovative solution for KRITI'25 - IIT Guwahati's inter-hostel technical competition organized by the Techboard IITG. Against fierce competition from 14 hostels, we secured **2nd place** with our hybrid analog-digital implementation that masterfully balanced the competition's strict constraints.

## 🚀 The Challenge

**Design an automated rain-detection and wiper control system with:**
- 4 discrete wiper speed levels (0°-180° motion)
- Visual LED speedometer display
- Wireless braking mechanism

**With brutal constraints:**
- 75% penalty for microcontrollers in core functions
- 25% penalty for timer ICs like NE555
- Full points only for pure analog/digital IC solutions
- Heavy penalties for manual control or incorrect indications

## 💡 Our Winning Solution

We developed a **strategic hybrid system** combining pure analog circuits for core functionality with targeted microcontroller use for bonus features:

### 🌧️ Rain Detection System
- **Custom copper trace sensor** with LM324 comparator
- Precision hysteresis circuit for noise immunity
- Calibrated to trigger at 2.5V (60% humidity threshold)

### ⚡ PWM Generation (Pure Analog)
- **ring oscillator** → 980Hz base clock
- **JK flip-flop** frequency divider → 490Hz
- **Logic gates** created four precise duty cycles:
  - 25% (slowest speed)
  - 50% 
  - 75%
  - 100% (full speed)

### 🎛️ Motor Control
- **Microswitch limiters** at 0° and 180° with mechanical debouncing
- **74HC74 D-flip-flop** for direction control
- **L293D motor driver** with analog PWM input

### 🖥️ Strategic Digital Components
- **Arduino Nano** for speedometer (no penalty!)
  - Controlled LED dashboard via transistor array
  - Positioned servo needle at 45° increments
- **IR braking system** 
  - IR receiver
  - Play → Emergency brake | Stop → Resume

## 🎯 Key Innovations

1. Hybrid architecture reducing our efforts 
2. Precision analog PWM generation
3. Mechanical debouncing system


Special thanks to:
- Our senior mentor [Keshav Baldeva] for guidance
- Teammates [Vasudev and Advaith] for the sleepless nights
- The 7408 IC that survived our experiments

