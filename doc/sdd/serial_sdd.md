# Software Detailed Design: Serial Communication Module

## Overview

The serial communication module provides functions to initialize the serial port and transmit radar data (angle and distance) to a serial monitor. This is useful for debugging and monitoring radar output in real time.

---

## Files

- `serial.h`: Header file declaring the serial communication interface.
- `serial.cpp`: Implementation of the serial communication functions.

---

## Functions

### 1. Serial_Init

- **Prototype:** `void Serial_Init(void);`
- **Description:** Initializes the serial port for communication at a baud rate of 115200.
- **Parameters:** None
- **Return:** None
- **Implementation Details:**
  - Calls `Serial.begin(BaudRate)` to set up the serial port.
  - `BaudRate` is defined as 115200.

**Pseudocode:**

```cpp
function Serial_Init():
    Serial.begin(115200)
```

---

### 2. Serial_PrintRadar

- **Prototype:** `void Serial_PrintRadar(int degree, int distance);`
- **Description:** Prints the radar scan angle and measured distance to the serial monitor.
- **Parameters:**
  - `degree`: The angle of the radar scan (integer).
  - `distance`: The measured distance from the radar (integer).
- **Return:** None
- **Implementation Details:**
  - Uses `Serial.print` and `Serial.println` to output formatted text:
    - Prints "Degree:  " followed by the degree value.
    - Prints ",Distance:   " followed by the distance value and a newline.

**Pseudocode:**

```cpp
function Serial_PrintRadar(degree, distance):
    Serial.print("Degree:  ")
    Serial.print(degree)
    Serial.print("    ,Distance:   ")
    Serial.println(distance)

```

---

## Constants

- `BaudRate`: Set to 115200 for serial communication speed.

---

## Dependencies

- Requires the Arduino `Serial` object and `USBAPI.h` for serial communication.

---

## Usage Example

```cpp
Serial_Init();
Serial_PrintRadar(90, 150);

```

This will initialize the serial port and print: `Degree:  90    ,Distance:   150` to the serial monitor.
