# RoboNeko

![Screenshot](logo.png?raw=true "Screenshot showing a happy Robit")

The classic Neko applet for X11, now with more robot! Written in C++ with SDL2.

Developed to learn and demonstrate cross-platform development with CMake.

Due to limitations with SDL the robot is confined to the window.

## Build Instructions

### macOS

Make sure the SDL2.framework is installed in /Library/Frameworks/.

[TODO]

### Linux

The build with CMake:

    cd RoboNeko
    mkdir build
    cd build
    cmake ..
    make

### Windows

Unpack the SDL2 development files and set the SDL2_DIR environment variable to point at the directory location. Also make sure that SDL2.dll is in a folder your path.

Opening the RoboNeko folder in Visual Studio 2017 will automatically create a project based on the CMake settings and allow you to build and debug from the IDE.
