@echo off
rem This script builds the Ultrasonic Radar project and Load the Firmware to the device
rem Make sure to run this script from the directory where platformio is located

echo Received parameter: %1

:: Check the first parameter and run the appropriate script
if /I "%1"=="RCC" (
    echo Running Test on Rodrigo's Computer...
    call C:\Users\rodri\.platformio\penv\Scripts\platformio.exe test -e uno -vvv
) else if /I "%1"=="LRV" (
    echo Running Test on Leticia's Computer...
    call C:\Users\rodri\.platformio\penv\Scripts\platformio.exe test -e uno_lrv -vvv
) else if /I "%1"=="LOGIC" (
    echo Running Test on Native...
    call C:\Users\rodri\.platformio\penv\Scripts\platformio.exe test -e native -vvv    
) else (
    echo Invalid parameter. Please use RCC, LRV, or LOGIC.
    echo Usage: Run_Test.cmd [RCC|LRV|LOGIC]
    exit /b 1
)

pause