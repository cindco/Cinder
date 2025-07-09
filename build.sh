#!/bin/bash
set -e

# Delete the build directory if it exists
if [ -d build ]; then
    echo "Deleting existing build directory..."
    rm -rf build
fi

# Create a new build directory
mkdir build
cd build

# Prompt user for build type
echo
read -p "Choose build option (1 = ALL samples, 2 = specific sample): " buildchoice

if [ "$buildchoice" == "1" ]; then
    cmake -DCINDER_BUILD_ALL_SAMPLES=ON ..
else
    read -p "Enter the sample path (relative to samples/, e.g. _opengl/Cube): " sample
    cmake -DCINDER_BUILD_SAMPLE=$sample ..
fi

cd ..
echo "Build folder regenerated and CMake configuration complete."

# Keep the terminal open if run interactively
if [[ $- == *i* ]]; then
    read -p "Press enter to exit..."
fi 