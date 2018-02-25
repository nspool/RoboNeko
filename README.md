# RoboNeko

![Screenshot](logo.png?raw=true "Screenshot showing a happy Robit")

The classic Neko applet for X11, now with more robot! Written in C++ with SDL2.

To learn and demonstrate cross-platform SDL development with CMake.

Due to limitations with SDL the robot is confined to the window.

## Build Instructions

### macOS

This has been tested with Xcode 9 with CMake 3.9.4.

Download the SDL2.framework and drag it into /Library/Frameworks/.

    git clone https://github.com/nspool/RoboNeko.git
    cd RoboNeko && mkdir build && cd build
    cmake -G Xcode ..
    open RoboNeko.xcodeproj

### Linux / BSD

Make sure the the SDL2 development libraries have been installed through your distribution's package manager.

    git clone https://github.com/nspool/RoboNeko.git
    cd RoboNeko && mkdir build && cd build
    cmake ..
    make

### Windows

Unpack the SDL2 development files and set the SDL2_DIR environment variable to point at the directory location. Also make sure that SDL2.dll is in a folder your path.

Opening the RoboNeko folder in Visual Studio 2017 will automatically create a project based on the CMake settings and allow you to build and debug from the IDE.
