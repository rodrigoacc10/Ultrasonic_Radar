@echo off
rem This script builds the Ultrasonic Radar project and Load the Firmware to the device
rem Make sure to run this script from the directory where platformio is located

call C:\Users\rodri\.platformio\penv\Scripts\platformio.exe run 
call C:\Users\rodri\.platformio\penv\Scripts\platformio.exe run --target upload 

pause