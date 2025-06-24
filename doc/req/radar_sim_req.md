# Radar Simulation System Requirements

## 1. Introduction

This document outlines the requirements for the Radar Simulation System, which performs ultrasonic radar distance measurement, servo control, and graphical visualization on an ST7735-based LCD. The system is designed for real-time radar data acquisition, display, and serial output for debugging and analysis.

---

## 2. Functional Requirements

### 2.1. System Initialization

- The system shall initialize serial communication at 115200 baud.
- The system shall initialize the LCD display and show a startup interface.
- The system shall configure the ultrasonic sensor and servo pins.
- The system shall perform an initial sweep of the servo to verify operation.

### 2.2. Radar Data Acquisition

- The system shall trigger the ultrasonic sensor to measure distance at each servo angle.
- The system shall calculate distance using the speed of sound and echo time.
- The system shall sweep the servo from maximum to minimum angle and back, covering the full radar range.

### 2.3. Data Display and Visualization

- The system shall display a radar background, scanlines, and detected points on the LCD.
- The system shall update the LCD with the current angle and measured distance.
- The system shall visually distinguish points within 1 meter and those beyond 1 meter.
- The system shall redraw the radar background and fixed labels as needed.

### 2.4. Serial Output

- The system shall output the current angle and measured distance to the serial monitor in a human-readable format.

### 2.5. Timing and Control

- The system shall control the servo movement with configurable step size and delay.
- The system shall ensure accurate timing for ultrasonic sensor triggering and echo measurement.

---

## 3. Non-Functional Requirements

### 3.1. Performance

- The system shall provide real-time updates to the LCD and serial output with minimal latency.
- The system shall operate reliably across the full range of servo motion.

### 3.2. Usability

- The LCD interface shall be clear and easy to interpret, showing radar sweeps and detected objects.
- Serial output shall be formatted for easy reading and debugging.

### 3.3. Maintainability

- The code shall be modular, with separate files for main logic, LCD control, and serial communication.
- All functions shall be documented with clear descriptions and parameter lists.

---

## 4. Hardware and Software Requirements

- Arduino-compatible microcontroller with sufficient I/O pins.
- ST7735-based 128x160 LCD display.
- Ultrasonic distance sensor (e.g., HC-SR04).
- Servo motor for radar sweep.
- Ucglib graphics library for LCD control.
- Arduino Servo and SPI libraries.

---

## 5. Example Use Case

1. Power on the system.
2. The LCD displays a startup screen, then the radar background.
3. The servo sweeps, and the system measures and displays distance at each angle.
4. Detected points are shown on the LCD; data is output to the serial monitor.

---

## 6. Memory Usage Targets and Status

| Memory Type | Target Usage         | Total Size (bytes) | Current Usage (%) | Current Used (bytes) |
|-------------|---------------------|--------------------|-------------------|----------------------|
| RAM         | < 80%               | 2048               | 34.8%             | 712                  |
| Flash       | < 90%               | 32256              | 76.1%             | 24538                |

---

These requirements ensure the Radar Simulation System provides accurate, real-time radar visualization and data output for development and analysis purposes.
