# Radar Simulation System Test Cases

## 1. Introduction

This document defines test cases for the Radar Simulation System, covering initialization, radar data acquisition, display, serial output, and error handling. Each test case includes a description, steps, expected results, and references to requirements.

---

## 2. Test Cases

### TC-01: System Initialization

- **Description:** Verify that the system initializes all hardware and displays the startup screen.
- **Steps:**
  1. Power on the system.
- **Expected Results:**
  - Serial communication is initialized at 115200 baud.
  - LCD displays the startup interface.
  - Servo performs an initial sweep.
- **Requirements:** 2.1

---

### TC-02: Ultrasonic Sensor Measurement

- **Description:** Verify that the system measures distance using the ultrasonic sensor at each servo angle.
- **Steps:**
  1. Allow the system to run through a full sweep.
- **Expected Results:**
  - Distance is measured at each servo position.
  - No missed or spurious readings.
- **Requirements:** 2.2

---

### TC-03: Radar Sweep and Display

- **Description:** Verify that the LCD displays radar background, scanlines, and detected points during operation.
- **Steps:**
  1. Observe the LCD during a full sweep.
- **Expected Results:**
  - Radar background and scanlines are visible.
  - Detected points are plotted at correct positions.
  - Points within 1 meter are shown in red; points beyond 1 meter in yellow.
- **Requirements:** 2.3

---

### TC-04: Serial Output Format

- **Description:** Verify that the serial output is formatted correctly and matches measured data.
- **Steps:**
  1. Connect to the serial monitor at 115200 baud.
  2. Observe output during a sweep.
- **Expected Results:**
  - Each line shows the current angle and distance in the format: `Degree:  <angle>    ,Distance:   <distance>`
- **Requirements:** 2.4

---

### TC-05: Servo Control and Timing

- **Description:** Verify that the servo moves smoothly and timing is consistent.
- **Steps:**
  1. Observe servo movement during operation.
- **Expected Results:**
  - Servo moves in defined steps and delays.
  - No jitter or missed steps.
- **Requirements:** 2.5

---

### TC-06: Error Handling (Sensor Disconnected)

- **Description:** Verify system behavior if the ultrasonic sensor is disconnected or fails.
- **Steps:**
  1. Disconnect the ultrasonic sensor.
  2. Power on and observe system behavior.
- **Expected Results:**
  - System does not crash.
  - Serial and LCD output indicate out-of-range or error values.
- **Requirements:** 3.1, 3.2

---

### TC-07: LCD Usability

- **Description:** Verify that the LCD interface is clear and easy to interpret.
- **Steps:**
  1. Observe the LCD during operation.
- **Expected Results:**
  - Radar sweeps and detected objects are clearly visible.
  - Labels and graphics are readable.
- **Requirements:** 3.2

---

### TC-08: Code Modularity and Documentation

- **Description:** Verify that the code is modular and well-documented.
- **Steps:**
  1. Review the source code.
- **Expected Results:**
  - Main logic, LCD, and serial communication are in separate files.
  - Functions have clear descriptions and parameter lists.
- **Requirements:** 3.3

---

## 3. Traceability Matrix

| Test Case | Requirement(s) | Test Status |
|-----------|----------------|-------------|
| TC-01     | 2.1            | Not Run     |
| TC-02     | 2.2            | Not Run     |
| TC-03     | 2.3            | Not Run     |
| TC-04     | 2.4            | Not Run     |
| TC-05     | 2.5            | Not Run     |
| TC-06     | 3.1, 3.2       | Not Run     |
| TC-07     | 3.2            | Not Run     |
| TC-08     | 3.3            | Not Run     |

---

These test cases ensure the Radar Simulation System meets its functional and non-functional requirements for reliable operation and usability.
