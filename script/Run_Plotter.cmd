@echo off
setlocal

rem Make sure to run this script with Python and required libraries installed

:menu
cls
echo ================================
echo       Select an Option
echo ================================
echo 1 - Plot Dynamic Graph
echo 2 - Plot Dynamic Graph and Save Data to CSV
echo 3 - Plot Static Graph
echo 4 - Exit
echo ================================
set /p choice=Enter your selection (1-4): 

:: Get the folder where this script is located
set "scriptDir=%~dp0"

:: Handle input
if "%choice%"=="1" (
    echo Plot Dynamic Graph...
    call python radar_serial_plot.py
    goto end
) else if "%choice%"=="2" (
    echo Plot Dynamic Graph and Save Data to CSV...
    call python radar_serial_plot_csv.py
    goto end
) else if "%choice%"=="3" (
    echo Plot Static Graph...
    call python radar_serial_plot_grid.py
    goto end
) else if "%choice%"=="4" (
    echo Exiting...
    goto end
) else (
    echo Invalid selection. Please try again.
    pause
    goto menu
)

:end
endlocal