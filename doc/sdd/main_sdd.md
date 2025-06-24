# Software Detailed Design: Main Application Module

## Overview

The main application module coordinates ultrasonic radar distance measurement, servo control, and graphical display on an ST7735-based LCD. It initializes hardware, manages the main control loop, and integrates the LCD and serial communication modules.

---

## File

- `main.cpp`: Main program file containing setup, loop, and core logic.

---

## Key Components and Constants

- **Ultrasonic Sensor Pins:** `trigPin`, `echoPin`
- **Servo Pin:** `ServoPin`
- **LCD Pins:** `Ucg_pin`, `Ucg_cs`, `Ucg_reset`
- **Screen Dimensions:** `Xmax`, `Ymax`, `Xcent`, `base`, `scanline`
- **Servo Angles and Steps:** `MaxServoAngle`, `MinServoAngle`, `ServoStep`, etc.
- **Timing Constants:** `delayTime`, `Ten_us`, `Two_us`
- **Distance Calculation Macro:** `DISTANCE_CALC(duration)`

---

## Objects

- `Servo baseServo`: Controls the radar's servo motor.
- `Ucglib_ST7735_18x128x160_HWSPI ucg`: LCD display object.

---

## Functions

### 1. setup

- **Prototype:** `void setup(void);`
- **Description:** Initializes serial communication, LCD, pins, and servo. Performs a test sweep of the servo.
- **Implementation Details:**
  - Calls `Serial_Init()` and `lcd_setup(&ucg)`.
  - Sets pin modes for ultrasonic sensor.
  - Attaches and initializes the servo.
  - Sweeps the servo from start to max angle for initial test.

**Pseudocode:**

```cpp
function setup():
    Serial_Init()
    lcd_setup(&ucg)
    pinMode(trigPin, OUTPUT)
    pinMode(echoPin, INPUT)
    baseServo.attach(ServoPin)
    baseServo.write(ServoInitAngle)
    for x = StartServoAngle to MaxServoAngle step ServoInitStep:
        baseServo.write(x)
        delay(delayTime)
```

---

### 2. calculateDistance

- **Prototype:** `int calculateDistance();`
- **Description:** Measures distance using the ultrasonic sensor.
- **Implementation Details:**
  - Triggers the ultrasonic sensor and measures echo time.
  - Converts echo time to distance using the speed of sound.

**Pseudocode:**

```cpp
function calculateDistance():
    digitalWrite(trigPin, LOW)
    delayMicroseconds(Two_us)
    digitalWrite(trigPin, HIGH)
    delayMicroseconds(Ten_us)
    digitalWrite(trigPin, LOW)
    duration = pulseIn(echoPin, HIGH)
    return DISTANCE_CALC(duration)
```

---

### 3. loop

- **Prototype:** `void loop(void);`
- **Description:** Main control loop. Sweeps the servo back and forth, measures distance, updates LCD and serial output.
- **Implementation Details:**
  - Draws radar background and fixed labels.
  - Sweeps servo from max to min angle, then min to max.
  - For each angle:
    - Moves servo
    - Draws scanline
    - Measures distance
    - Prints radar data to serial
    - Draws radar point on LCD
  - Clears and redraws background between sweeps.

**Pseudocode:**

```cpp
function loop():
    lcd_background(&ucg, Xcent, base, Xmax)
    lcd_fix_font(&ucg)
    for x = MaxServoAngle downto MinServoAngleRange step ServoStep:
        baseServo.write(x)
        lcd_DrawScanlines(&ucg, x, Xcent, base, scanline, false)
        distance = calculateDistance()
        Serial_PrintRadar(x, distance)
        lcd_PrintPoint(&ucg, x, distance, Xcent, base)
    delay(delayTime)
    lcd_cls(&ucg)
    lcd_background(&ucg, Xcent, base, Xmax)
    lcd_fix_font(&ucg)
    for x = MinServoAngle to MaxServoAngleRange step ServoStep:
        baseServo.write(x)
        lcd_DrawScanlines(&ucg, x, Xcent, base, scanline, true)
        distance = calculateDistance()
        Serial_PrintRadar(x, distance)
        lcd_PrintPoint(&ucg, x, distance, Xcent, base)
    delay(delayTime)
    lcd_cls(&ucg)
```

---

## Dependencies

- LCD display module (`lcd.h`)
- Serial communication module (`serial.h`)
- Servo and SPI libraries
- Ucglib graphics library

---

## Usage Flow

1. System initializes hardware and performs a servo sweep.
2. Main loop alternates sweeping the servo left and right.
3. At each angle, the system measures distance, updates the LCD, and prints data to serial.

---

## Example Output

- LCD displays radar sweep, scanlines, and detected points.
- Serial monitor outputs: `Degree:  90    ,Distance:   150`

---

This design enables real-time radar visualization and data output for debugging and analysis.
