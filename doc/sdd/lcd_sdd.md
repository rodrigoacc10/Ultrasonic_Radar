# Software Detailed Design: LCD Display Module

## Overview

The LCD display module provides functions to initialize, clear, and render graphics and radar data on an ST7735-based LCD using the Ucglib graphics library. It supports drawing backgrounds, scanlines, radar points, displaying text information, and showing animated welcome messages.

---

## Files

- `lcd.h`: Header file declaring the LCD interface functions and pin definitions.
- `lcd.cpp`: Implementation of the LCD display functions.

---

## Functions

### 1. lcd_initialize

- **Prototype:** `void lcd_initialize(Ucglib_ST7735_18x128x160_HWSPI *ucg, const char *message1[], const char *message2[], const char *message3[]);`
- **Description:** Initializes the LCD and displays a series of welcome messages with visual effects.
- **Parameters:**
  - `ucg`: Pointer to the Ucglib display object.
  - `message1`, `message2`, `message3`: Arrays of two strings each, to be displayed in sequence.
- **Return:** None
- **Implementation Details:**
  - Calls `lcd_displayTextWithEffectsInTwoLines` for each message array, with a set display duration (2500 ms).

---

### 2. lcd_displayTextWithEffectsInTwoLines

- **Prototype:** `void lcd_displayTextWithEffectsInTwoLines(Ucglib_ST7735_18x128x160_HWSPI *ucg, const char *message[], int duration);`
- **Description:** Displays two lines of text with background gradient and color effects for a specified duration.
- **Parameters:**
  - `ucg`: Pointer to the Ucglib display object.
  - `message`: Array of two strings to display.
  - `duration`: Duration in milliseconds for the effect.
- **Return:** None
- **Implementation Details:**
  - Clears the screen, sets up a gradient background, and prints two lines of text with a fixed font and color.
  - Waits for the specified duration before returning.

---

### 3. lcd_setup

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

### 4. lcd_cls

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

### 5. lcd_fix_font

- **Prototype:** `void lcd_fix_font(Ucglib_ST7735_18x128x160_HWSPI *ucg);`
- **Description:** Sets font color and prints fixed distance labels on the LCD.
- **Parameters:**
  - `ucg`: Pointer to the Ucglib display object.
- **Return:** None
- **Implementation Details:**
  - Prints "100cm", "75cm", "50cm", and "25cm" at fixed positions with a green color.

---

### 6. lcd_background

- **Prototype:** `void lcd_background(Ucglib_ST7735_18x128x160_HWSPI *ucg, int Xcent, int base, int Xmax);`
- **Description:** Draws the radar background, including circles, lines, and decorative elements.
- **Parameters:**
  - `ucg`: Pointer to the Ucglib display object.
  - `Xcent`: X center coordinate.
  - `base`: Y base coordinate.
  - `Xmax`: Maximum X coordinate.
- **Return:** None
- **Implementation Details:**
  - Draws concentric circles, a base line, scale marks, and decorative boxes and shapes with various colors.

---

### 7. lcd_PrintRadar

- **Prototype:** `void lcd_PrintRadar(Ucglib_ST7735_18x128x160_HWSPI *ucg, int degree, int distance);`
- **Description:** Prints the radar angle and distance at the bottom of the LCD.
- **Parameters:**
  - `ucg`: Pointer to the Ucglib display object.
  - `degree`: Angle in degrees.
  - `distance`: Distance in centimeters.
- **Return:** None
- **Implementation Details:**
  - Prints "DEG: <degree>" and "<distance>cm" at fixed positions with blue color.

---

### 8. lcd_PrintPoint

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
  - Draws a red disc for distances < 100 cm, yellow for >= 100 cm.
  - Calls `lcd_fix_font` if the degree is between 70 and 110.
  - Calls `lcd_PrintRadar` to update the radar info.

---

### 9. lcd_DrawScanlines

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
  - Uses helper functions to calculate scanline steps and draws lines in green, dark green, and black.

---

### 10. Helper Functions

- **lcd_calculate_scanline_initial**
  - **Prototype:** `int lcd_calculate_scanline_initial(int x, bool add);`
  - **Description:** Returns `x + 4` if `add` is true, else `x - 4`.
- **lcd_calculate_scanline_step**
  - **Prototype:** `int lcd_calculate_scanline_step(int x, bool add);`
  - **Description:** Returns `x + 2` if `add` is true, else `x - 2`.

---

## Dependencies

- Requires the Ucglib graphics library for display operations.
- Uses trigonometric functions (`cos`, `sin`, `radians`) for drawing.
- May use Arduino functions like `delay`, `random`, and `millis`.

---

## Usage Example

```cpp
const char* message1[2] = {"Embeded Pipeline", "Cloud to Hardware"};
const char* message2[2] = {"Github:", "lruizv"};
const char* message3[2] = {"Github:", "rodrigoacc10"};
lcd_initialize(&ucg, message1, message2, message3);
lcd_setup(&ucg);
lcd_background(&ucg, 80, 120, 160);
lcd_PrintRadar(&ucg, 90, 50);
lcd_PrintPoint(&ucg, 90, 50, 80, 120);
lcd_DrawScanlines(&ucg, 90, 80, 120, 100, true);
```

This sequence initializes the display, shows welcome messages, draws the radar background, and renders radar data and scanlines.
