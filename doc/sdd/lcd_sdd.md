# Software Detailed Design: LCD Display Module

## Overview

The LCD display module provides functions to initialize, clear, and render graphics and radar data on an ST7735-based LCD using the Ucglib graphics library. It supports drawing backgrounds, scanlines, radar points, and displaying text information.

---

## Files

- `lcd.h`: Header file declaring the LCD interface functions.
- `lcd.cpp`: Implementation of the LCD display functions.

---

## Functions

### 1. lcd_setup

- **Prototype:** `void lcd_setup(Ucglib_ST7735_18x128x160_HWSPI *ucg);`
- **Description:** Initializes the LCD screen, sets orientation, and displays a startup interface.
- **Parameters:**
  - `ucg`: Pointer to the Ucglib display object.
- **Return:** None
- **Implementation Details:**
  - Calls `ucg->begin` and sets rotation.
  - Sets font, colors, and prints startup messages.
  - Calls `lcd_cls` to clear the screen.

**Pseudocode:**

```cpp
function lcd_setup(ucg):
    ucg.begin()
    ucg.setRotate90()
    // Set colors, fonts, and print startup text
    lcd_cls(ucg)
    ucg.setFont(...)
```

---

### 2. lcd_cls

- **Prototype:** `void lcd_cls(Ucglib_ST7735_18x128x160_HWSPI *ucg);`
- **Description:** Clears the LCD screen by drawing black boxes over the display area.
- **Parameters:**
  - `ucg`: Pointer to the Ucglib display object.
- **Return:** None
- **Implementation Details:**
  - Sets color to black and fills the screen with boxes in a nested loop.

**Pseudocode:**

```cpp
function lcd_cls(ucg):
    ucg.setColor(black)
    for s in 0..128 step 8:
        for t in 0..160 step 16:
            ucg.drawBox(t, s, 16, 8)
```

---

### 3. lcd_fix_font

- **Prototype:** `void lcd_fix_font(Ucglib_ST7735_18x128x160_HWSPI *ucg);`
- **Description:** Sets font color and prints fixed distance labels on the LCD.
- **Parameters:**
  - `ucg`: Pointer to the Ucglib display object.
- **Return:** None

---

### 4. lcd_background

- **Prototype:** `void lcd_background(Ucglib_ST7735_18x128x160_HWSPI *ucg, int Xcent, int base, int Xmax);`
- **Description:** Draws the radar background, including circles, lines, and decorative elements.
- **Parameters:**
  - `ucg`: Pointer to the Ucglib display object.
  - `Xcent`: X center coordinate.
  - `base`: Y base coordinate.
  - `Xmax`: Maximum X coordinate.
- **Return:** None

---

### 5. lcd_PrintRadar

- **Prototype:** `void lcd_PrintRadar(Ucglib_ST7735_18x128x160_HWSPI *ucg, int degree, int distance);`
- **Description:** Prints the radar angle and distance at the bottom of the LCD.
- **Parameters:**
  - `ucg`: Pointer to the Ucglib display object.
  - `degree`: Angle in degrees.
  - `distance`: Distance in centimeters.
- **Return:** None

---

### 6. lcd_PrintPoint

- **Prototype:** `void lcd_PrintPoint(Ucglib_ST7735_18x128x160_HWSPI *ucg, int degree, int distance, int Xcent, int base);`
- **Description:** Draws a radar point at the calculated position and prints radar data.
- **Parameters:**
  - `ucg`: Pointer to the Ucglib display object.
  - `degree`: Angle in degrees.
  - `distance`: Distance in centimeters.
  - `Xcent`: X center coordinate.
  - `base`: Y base coordinate.
- **Return:** None
- **Implementation Details:**
  - Draws a red or yellow disc depending on distance.
  - Calls `lcd_fix_font` and `lcd_PrintRadar` as needed.

---

### 7. lcd_DrawScanlines

- **Prototype:** `void lcd_DrawScanlines(Ucglib_ST7735_18x128x160_HWSPI *ucg, int degree, int Xcent, int base, int scanline, bool direction);`
- **Description:** Draws radar scanlines based on angle, center, base, length, and direction.
- **Parameters:**
  - `ucg`: Pointer to the Ucglib display object.
  - `degree`: Angle in degrees.
  - `Xcent`: X center coordinate.
  - `base`: Y base coordinate.
  - `scanline`: Length of the scanline.
  - `direction`: Direction of scanline (true=clockwise, false=counterclockwise).
- **Return:** None
- **Implementation Details:**
  - Uses helper functions to calculate scanline steps and draws lines in different colors.

---

### 8. Helper Functions

- `lcd_calculate_scanline_initial(int x, bool add)`: Returns `x + 4` if `add` is true, else `x - 4`.
- `lcd_calculate_scanline_step(int x, bool add)`: Returns `x + 2` if `add` is true, else `x - 2`.

---

## Dependencies

- Requires the Ucglib graphics library for display operations.
- Uses trigonometric functions (`cos`, `sin`, `radians`) for drawing.
- May use Arduino functions like `delay` and `random`.

---

## Usage Example

```cpp
lcd_setup(&ucg);
lcd_background(&ucg, 80, 120, 160);
lcd_PrintRadar(&ucg, 90, 50);
lcd_PrintPoint(&ucg, 90, 50, 80, 120);
lcd_DrawScanlines(&ucg, 90, 80, 120, 100, true);
```

This sequence initializes the display, draws the radar background, and renders radar data and scanlines.
