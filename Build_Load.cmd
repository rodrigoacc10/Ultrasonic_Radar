@echo off
rem This script builds the Ultrasonic Radar project and Load the Firmware to the device
rem Make sure to run this script from the directory where platformio is located

echo Building the project...
call C:\Users\rodri\.platformio\penv\Scripts\platformio.exe run -e uno -vvv
echo Uploading the firmware...
call C:\Users\rodri\.platformio\penv\Scripts\platformio.exe run --target upload -e uno -vvv
echo Exiting...
goto end

:end
endlocal