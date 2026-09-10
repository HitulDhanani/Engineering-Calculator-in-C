@echo off
setlocal enabledelayedexpansion

echo =======================================================
echo  Building Engineering Calculator in C (Windows Script)
echo =======================================================

if not exist bin mkdir bin

:: Check PATH first
where gcc >nul 2>nul
if %errorlevel% equ 0 (
    set "COMPILER=gcc"
    goto :compile
)

where clang >nul 2>nul
if %errorlevel% equ 0 (
    set "COMPILER=clang"
    goto :compile
)

:: Check LLVM-MinGW winget path
set "WINGET_GCC=C:\Users\pritd\AppData\Local\Microsoft\WinGet\Packages\MartinStorsjo.LLVM-MinGW.UCRT_Microsoft.Winget.Source_8wekyb3d8bbwe\llvm-mingw-20260616-ucrt-x86_64\bin\gcc.exe"
if exist "%WINGET_GCC%" (
    set "COMPILER=%WINGET_GCC%"
    goto :compile
)

echo [WARNING] No GCC or Clang compiler found in system PATH.
echo You can:
echo  1. Install MinGW-w64 or LLVM.
echo  2. Use Code::Blocks, Dev-C++, or VS Code with C/C++ extension.
echo  3. Copy calculator_single_file.c directly into an online compiler like https://www.onlinegdb.com/
pause
exit /b 1

:compile
echo [INFO] Using compiler: %COMPILER%
"%COMPILER%" -Wall -Wextra -std=c99 -Iinclude src\main.c src\arithmetic.c src\electrical.c src\units.c src\ice_sensors.c src\utils.c -o bin\calculator.exe -lm
if %errorlevel% equ 0 (
    echo [SUCCESS] Binary created at bin\calculator.exe
    echo Running application...
    echo.
    bin\calculator.exe
    exit /b 0
) else (
    echo [ERROR] Compilation failed.
    pause
    exit /b 1
)
