# IUBPC Robotics Challenge - Arduino Solution Code

Welcome to the official repository containing solution code for the **IUBPC Robotics Challenge**. This collection provides fully tested Arduino Uno sketches for 9 hands-on robotics and electronics challenge cards ranging from fundamental digital output to complex state-machine sensor integrations and the final Boss Vault challenge.

---

## 📋 Overview of Challenge Solutions

| Project # | Project Name | Main Components | Key Concepts |
| :--- | :--- | :--- | :--- |
| **01** | [Traffic Light](./01_Traffic_Light/01_Traffic_Light.ino) | 3 LEDs (Red, Yellow, Green), Resistors | Digital output timing, state sequencing |
| **02** | [Button Switch](./02_Button_Switch/02_Button_Switch.ino) | Pushbutton, Built-in LED (Pin 13) | `INPUT_PULLUP`, active-low input reading |
| **03** | [SOS Signal](./03_SOS_Signal/03_SOS_Signal.ino) | Built-in LED / External LED | Morse code timing (`... --- ...`), modular functions |
| **04** | [Parking Sensor](./04_Parking_Sensor/04_Parking_Sensor.ino) | HC-SR04 Ultrasonic Sensor, Buzzer | `pulseIn()`, distance calculation, `map()`, audio feedback |
| **05** | [Night Light](./05_Night_Light/05_Night_Light.ino) | LDR (Light Dependent Resistor), LED | `analogRead()`, Serial debugging, threshold switching |
| **06** | [Smart Door](./06_Smart_Door/06_Smart_Door.ino) | Servo Motor, Pushbutton | `Servo.h` library, PWM angular control, automated hold delay |
| **07** | [Intruder Alarm](./07_Intruder_Alarm/07_Intruder_Alarm.ino) | HC-SR04 Sensor, Buzzer, LED, Pushbutton | State latching (armed/disarmed), multi-sensor logic |
| **08** | [Reaction Game](./08_Reaction_Game/08_Reaction_Game.ino) | LED, Pushbutton, Serial Monitor | `millis()`, `random()`, millisecond precision timing |
| **09 (BOSS)** | [The Vault](./09_Boss_Vault/09_Boss_Vault.ino) | Servo, HC-SR04 Sensor, Buzzer, Red/Green LEDs, Pushbutton | State machine (`LOCKED`, `OPEN`, `LOCKOUT`), proximity wake-up, secret knock code (`S-S-L-S`), debouncing, fail lockout |

---

## 🛠 Hardware & Hardware Pinout Summary

### Board Compatibility
- **Microcontroller**: Arduino Uno (or compatible board such as Nano, Mega)
- **Programming Environment**: Arduino IDE / VS Code with PlatformIO

### Hardware Connections Quick Reference

#### 1. Traffic Light
- **Pin 8**: Red LED
- **Pin 9**: Yellow LED
- **Pin 10**: Green LED

#### 2. Button Switch
- **Pin 2**: Pushbutton (Input Pullup to GND)
- **Pin 13**: LED Output

#### 3. SOS Signal
- **Pin 13**: LED Output (Blinks S-O-S pattern in Morse code)

#### 4. Parking Sensor
- **Pin 7**: HC-SR04 Trigger (`TRIG`)
- **Pin 6**: HC-SR04 Echo (`ECHO`)
- **Pin 8**: Piezo Buzzer

#### 5. Night Light
- **Pin A0**: Photoresistor (LDR) Voltage Divider
- **Pin 13**: Night Light LED Output

#### 6. Smart Door
- **Pin 2**: Door Trigger Button (`INPUT_PULLUP`)
- **Pin 9**: Servo Motor Control (`PWM`)

#### 7. Intruder Alarm
- **Pin 7**: HC-SR04 Trigger (`TRIG`)
- **Pin 6**: HC-SR04 Echo (`ECHO`)
- **Pin 2**: Reset / Disarm Button (`INPUT_PULLUP`)
- **Pin 8**: Alarm Buzzer
- **Pin 13**: Visual Alarm LED

#### 8. Reaction Time Game
- **Pin A0**: Floating pin for `randomSeed()`
- **Pin 2**: Reaction Trigger Button (`INPUT_PULLUP`)
- **Pin 13**: Target Signal LED

#### 9. BOSS: The Vault
- **Pin 2**: Knock Pattern Button (`INPUT_PULLUP`)
- **Pin 6**: HC-SR04 Echo (`ECHO`)
- **Pin 7**: HC-SR04 Trigger (`TRIG`)
- **Pin 8**: Audio Feedback Buzzer
- **Pin 9**: Servo Lock Mechanism (`PWM`)
- **Pin 12**: Green LED (Unlocked Status)
- **Pin 13**: Red LED (Locked Status / Lockout Flasher)

---

## 🚀 Getting Started

1. **Clone the Repository**:
   ```bash
   git clone https://github.com/ahlam26824/IUBPC_Arduino_Solution_Code.git
   cd IUBPC_Arduino_Solution_Code
   ```

2. **Open in Arduino IDE**:
   - Open any `.ino` file inside its respective subfolder (e.g., `09_Boss_Vault/09_Boss_Vault.ino`).
   - Select Board: **Arduino Uno**.
   - Select your COM Port and click **Upload**.

3. **Serial Monitor**:
   - For **05_Night_Light**, **08_Reaction_Game**, and **09_Boss_Vault**, open the Serial Monitor at **9600 baud rate** to view real-time logs, threshold readings, and state machine event logging.

---

## 📜 License

This solution repository is created for educational and competition purposes for the **IUBPC Robotics Challenge**. Free to use and modify!
