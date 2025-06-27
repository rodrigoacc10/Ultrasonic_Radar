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
- `const char* message1[2]`, `message2[2]`, `message3[2]`: Welcome and author messages displayed on the LCD at startup.

---

## Functions

### 1. setup

- **Prototype:** `void setup(void);`
- **Description:** Initializes the LCD with welcome messages, serial communication, LCD, and IO hardware (servo and ultrasonic module).
- **Implementation Details:**
  - Calls `lcd_initialize(&ucg, message1, message2, message3)` to display welcome messages.
  - Calls `Serial_Init()` and `lcd_setup(&ucg)`.
  - Calls `iohw_setup(&baseServo)` to initialize IO hardware, including the servo and ultrasonic module.

**Pseudocode:**

```cpp
function setup():
    lcd_initialize(&ucg, message1, message2, message3)
    Serial_Init()
    lcd_setup(&ucg)
    iohw_setup(&baseServo)
```

---

### 2. loop

- **Prototype:** `void loop(void);`
- **Description:** Main control loop. Sweeps the servo back and forth, measures distance, updates LCD and serial output using IO hardware abstraction.
- **Implementation Details:**
  - Draws radar background and fixed labels.
  - Sweeps servo from max to min angle, then min to max.
  - For each angle:
    - Moves servo
    - Draws scanline
    - Measures distance using `iohw_calculateDistance()`
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
        distance = iohw_calculateDistance()
        Serial_PrintRadar(x, distance)
        lcd_PrintPoint(&ucg, x, distance, Xcent, base)
    delay(delayTime)
    lcd_cls(&ucg)
    lcd_background(&ucg, Xcent, base, Xmax)
    lcd_fix_font(&ucg)
    for x = MinServoAngle to MaxServoAngleRange step ServoStep:
        baseServo.write(x)
        lcd_DrawScanlines(&ucg, x, Xcent, base, scanline, true)
        distance = iohw_calculateDistance()
        Serial_PrintRadar(x, distance)
        lcd_PrintPoint(&ucg, x, distance, Xcent, base)
    delay(delayTime)
    lcd_cls(&ucg)
```

---

## Dependencies

- LCD display module (`lcd.h`)
- Serial communication module (`serial.h`)
- IO hardware abstraction module (`io_hw.h`)
- Servo and SPI libraries
- Ucglib graphics library

---

## Usage Flow

1. System initializes LCD with welcome messages, serial, and IO hardware.
2. Main loop alternates sweeping the servo left and right.
3. At each angle, the system measures distance, updates the LCD, and prints data to serial.

---

## Example Output

- LCD displays welcome messages, radar sweep, scanlines, and detected points.
- Serial monitor outputs: `Degree:  90    ,Distance:   150`

---

This design enables real-time radar visualization and data output for debugging and analysis.
