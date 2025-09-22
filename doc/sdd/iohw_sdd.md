# Software Detailed Design: IO Hardware Abstraction Module

## Overview

The IO hardware abstraction module (`io_hw.h`/`io_hw.cpp`) provides functions and definitions for initializing and controlling the hardware interfaces for the radar system, including the ultrasonic sensor and servo motor. It encapsulates pin assignments, timing constants, and hardware setup, enabling modular and maintainable code.

---

## Files

- `io_hw.h`: Header file declaring the IO hardware interface and constants.
- `io_hw.cpp`: Implementation of the IO hardware functions.

---

## Constants and Macros

- **Pin Assignments:**
  - `trigPin`: Ultrasonic trigger pin (D6)
  - `echoPin`: Ultrasonic echo pin (D5)
  - `ServoPin`: Servo control pin (D3)
- **Timing Constants:**
  - `Ten_us`: 10 microseconds (ultrasonic trigger pulse)
  - `Two_us`: 2 microseconds (ultrasonic trigger delay)
  - `delayTime`: 50 ms (servo movement delay)
- **Servo Parameters:**
  - `MaxServoAngle`, `MinServoAngle`, `StartServoAngle`, `MaxServoAngleRange`, `MinServoAngleRange`, `ServoStep`, `ServoInitStep`, `ServoInitAngle`
- **Distance Calculation Macro:**
  - `DISTANCE_CALC(duration)`: Converts echo time to distance in centimeters

---

## Functions

### 1. iohw_setup

- **Prototype:** `void iohw_setup(Servo *baseServo);`
- **Description:** Initializes the ultrasonic sensor and servo hardware. Sets pin modes, attaches the servo, sets its initial angle, and performs a test sweep.
- **Parameters:**
  - `baseServo`: Pointer to the Servo object representing the base servo.
- **Return:** None
- **Implementation Details:**
  - Sets pin modes for `trigPin` and `echoPin`.
  - Attaches the servo to `ServoPin` and sets to initial angle.
  - Sweeps the servo from start to max angle in steps, with delays, to verify operation.

**Pseudocode:**

```cpp
function iohw_setup(baseServo):
    pinMode(trigPin, OUTPUT)
    pinMode(echoPin, INPUT)
    baseServo.attach(ServoPin)
    baseServo.write(ServoInitAngle)
    for x = StartServoAngle to MaxServoAngle step ServoInitStep:
        baseServo.write(x)
        delay(delayTime)
```

---

### 2. iohw_calculateDistance

- **Prototype:** `int iohw_calculateDistance();`
- **Description:** Measures distance using the ultrasonic sensor by triggering a pulse and measuring the echo time.
- **Parameters:** None
- **Return:** The calculated distance in centimeters (int).
- **Implementation Details:**
  - Triggers the ultrasonic sensor by toggling `trigPin` with precise delays.
  - Measures the echo time using `pulseIn` on `echoPin`.
  - Converts the echo time to distance using the speed of sound macro.

**Pseudocode:**

```cpp
function iohw_calculateDistance():
    digitalWrite(trigPin, LOW)
    delayMicroseconds(Two_us)
    digitalWrite(trigPin, HIGH)
    delayMicroseconds(Ten_us)
    digitalWrite(trigPin, LOW)
    duration = pulseIn(echoPin, HIGH)
    return DISTANCE_CALC(duration)
```

---

## Dependencies

- Arduino core (for `pinMode`, `digitalWrite`, `delay`, `pulseIn`)
- Servo library

---

## Usage Example

```cpp
Servo baseServo;
iohw_setup(&baseServo);
int distance = iohw_calculateDistance();
```

This sequence initializes the hardware and reads a distance measurement from the ultrasonic sensor.
