@echo off
setlocal

:menu
cls
echo ================================
echo       Select an Option
echo ================================
echo 1 - Run Hardware Test on Rodrigo's Computer and Board (RCC)
echo 2 - Run Hardware Test on Leticia's Computer and Board (LRV)
echo 3 - Run Hardware Test on Native Using Google Test (LOGIC)
echo 4 - Run Static Code Analysis on Native using PlatformIO (STATIC)
echo 5 - Exit (EXIT)
echo ================================
set /p choice=Enter your selection (1-4): 

rem This script builds the Ultrasonic Radar project and Load the Firmware to the device
rem Make sure to run this script from the directory where platformio is located

:: Check the first parameter and run the appropriate script
if /I %choice%=="RCC" (
    echo Running Test on Rodrigo's Computer...
    call C:\Users\rodri\.platformio\penv\Scripts\platformio.exe test -e uno -vvv
    goto end    
) else if /I %choice%=="LRV" (
    echo Running Test on Leticia's Computer...
    call C:\Users\rodri\.platformio\penv\Scripts\platformio.exe test -e uno_lrv -vvv
    goto end    
) else if /I %choice%=="LOGIC" (
    echo Running Test on Native...
    call C:\Users\rodri\.platformio\penv\Scripts\platformio.exe test -e native -vvv   
    goto end     
) else if /I %choice%=="STATIC" (
    echo Running Static Code Analysis on Native...
    call C:\Users\rodri\.platformio\penv\Scripts\platformio.exe check -e native -vvv     
    goto end    
) else if "%choice%"=="EXIT" (
    echo Exiting...
    goto end    
) else (
    echo Invalid parameter.Please try again.
    pause
    goto menu
)

:end
endlocal