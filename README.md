# Arduino Radar Project Guide

Welcome! This guide will help you set up, build, and upload your Arduino Radar project using VS Code and PlatformIO.

> **Note:** This project and its code are not owned by the repository user. The code is open source and is used here for educational purposes only.

---

## Prerequisites

- **VS Code**  
  [Download VS Code](https://code.visualstudio.com/)

  - **PlatformIO Core** (CLI)  
    - We'll use PlatformIO, which integrates with VS Code.

- **Arduino IDE** (optional, for board drivers)  
  - [Download Arduino IDE (Windows/Linux/Mac)](https://www.arduino.cc/en/software)

- **Install CH340 Driver** ( CH340 is a TTL (serial) to USB converter and vice versa.)  
  - [Download CH340 Driver Windows](https://cdn.sparkfun.com/assets/learn_tutorials/8/4/4/CH341SER.EXE)
  - [Download CH340 Driver Linux](https://cdn.sparkfun.com/assets/learn_tutorials/8/4/4/CH341SER_LINUX.ZIP)
  - [Download CH340 Driver Mac](https://cdn.sparkfun.com/assets/learn_tutorials/8/4/4/CH341SER_MAC.ZIP)
  - [More Info at "How to Install CH340 Drivers"](https://learn.sparkfun.com/tutorials/how-to-install-ch340-drivers/all)

---

## Step 1: Install PlatformIO Extension

1. Open **VS Code**.
2. Go to **Extensions** (`Ctrl+Shift+X` or click the square icon).
3. Search for **"PlatformIO IDE"**.
4. Click **Install**.

*This installs PlatformIO Core, templates, and upload utilities.*

---

## Step 2: Open the Project Folder

**Option A: Using the File Menu:**

1. Go to **File > Open Folder...**
2. Navigate to your project folder (should contain `platformio.ini`).
3. Click **Select Folder** (or **Open** on macOS).

**After opening, you should see:**

- `.pio` folder (hidden, auto-generated)
- `platformio.ini` (project config)
- `src/` folder (source files)

*VS Code may display “PlatformIO is initializing” — wait a few seconds.*

---

## Step 3: Check Your Code

- Open `src/main.cpp` to review or edit your main code.

---

## Step 4: Build (Compile) the Project

- Click the **checkmark icon (✓)** in the bottom bar  
  **OR**  
  Press `Ctrl+Shift+P` → search for **PlatformIO: Build**

*PlatformIO will compile your code and show errors/output in the terminal.*

---

## Step 5: Connect the Arduino Board

1. Plug your Arduino board into your computer via USB.
2. Confirm which **COM port** it's using:
   - **Windows:** Check Device Manager → "Ports (COM & LPT)"
   - **macOS/Linux:** Run `ls /dev/tty.*` or `ls /dev/ttyUSB*` in the terminal

---

## Step 6: Upload Code to the Board

- Click the **right arrow icon (→)** in the bottom bar  
  **OR**  
  Press `Ctrl+Shift+P` → **PlatformIO: Upload**

*PlatformIO will auto-detect the port (or use the one in `platformio.ini`) and upload the firmware.*

---

## Optional: Set the Serial Monitor

- Click the **plug icon (🔌)** in the status bar to open the Serial Monitor.

---

## Optional: Python Serial Plotter

### Usage

1. Verify the COM port and baud rate.
2. Run the script. Execute: `python radar_serial_plot_grid.py`
3. Click **Start** to begin plotting.
4. Click **Stop** to halt data acquisition.

---

## Optional: Remote Upload

In the host machine:

1. Log in with your PlatformIO account
2. Go to the Tokens section
3. Click "Generate New Token"
4. Execute in Platformio CLi: `pio remote agent start --name radar_agent`
5. In a new Plaformio CLi window execute: `pio remote agent list`
     - **Do not close the cmd with where the remote agent was start**
6. Execute in Platformio CLi: `pio device list`
7. Share Token and Device Port

Remote Machine:

1. Add token from host machine as Environmental Variable in the Remote Machine
   - PLATFORMIO_AUTH_TOKEN="your_token_here"
2. Configure `upload_port=` in the platformio.ini
3. Execute in Platformio CLi: `pio remote --agent radar_agent run --target upload`

---

## Project Structure

```text
Ultrasonic_Radar/
├── Ultrasonic_Radar/
│   ├── doc/
│   │   └── python/
│   │       └── py_scripts_design.md         # Python scripts detailed design document
│   │   └── req/
│   │       └── radar_sim_req.md         # Project Requirements
│   │   └── sdd/
│   │       └── lcd_sdd.md              # LCD module software detailed design
│   │       └── iohw_sdd.md             # IOHW module software detailed design
│   │       └── main_sdd.md             # Main module software detailed design
│   │       └── serial_sdd.md           # Serial module software detailed design
│   │   └── tst/
│   │       └── radar_sim_tst.md         # Project Test
│   │   └── RepoStructure.md             # Repository Structure
│   ├── include/
│   │   └── lcd.h                      # LCD module header
│   │   └── io_hw.h                    # IOHW module header
│   │   └── serial.h                   # Serial module header
│   │   └── README.md                  # readme
│   ├── lib/                           # External libraries
│   ├── script/
│   │   └── radar_serial_plot_grid.py  # Python serial plotter script
│   ├── src/
│   │   ├── lcd.cpp                    # LCD module implementation
│   │   └── main.cpp                   # Main code
│   │   ├── io_hw.cpp                  # IOHW module implementation
│   │   ├── serial.cpp                 # Serial module implementation
│   ├── test/
│   │   └── test_main/
│   │       └── test_main.cpp          # Test code
│   │   └── test_lcd/
│   │       └── test_lcd.cpp          # Test code
│   │   └── test_servo/
│   │       └── test_servo.cpp          # Test code
│   ├── .gitignore                       # Git ignore file
│   ├── platformio.ini                   # Project configuration
│   └── README.md                        # Project guide and documentation
```
