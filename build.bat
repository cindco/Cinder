@echo off
setlocal

REM Delete the build directory if it exists
if exist build (
    echo Deleting existing build directory...
    rmdir /s /q build
)

REM Create a new build directory
mkdir build
cd build

REM Prompt user for build type
echo.
echo Choose build option:
echo   1. Build ALL samples
echo   2. Build a specific sample
set /p buildchoice="Enter 1 or 2: "

if "%buildchoice%"=="1" (
    cmake -DCINDER_BUILD_ALL_SAMPLES=ON ..
) else (
    set /p sample="Enter the sample path (relative to samples/, e.g. _opengl/Cube): "
    cmake -DCINDER_BUILD_SAMPLE=%sample% ..
)

cd ..
echo Build folder regenerated and CMake configuration complete.
pause 