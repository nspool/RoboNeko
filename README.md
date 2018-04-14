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

#### Code::Blocks

Code::Blocks appears to only support a 32-bit version of MinGW. This will work fine provided that SDL2.dll is 32-bit.

Download the SDL2 development files and from the command prompt set the SDL2_DIR environment variable with UNIX-style forward slash:

    setx SDL2_DIR C:/SDL-2.0.7

Close and reopen the command prompt and create the Code::Blocks project file with CMake:

    cd RoboNeko
    mkdir build
    cd build
    cmake -G "CodeBlocks" ..

Then open RoboNeko.cbp in the Code::Blocks IDE.

#### Visual Studio

Unpack the SDL2 development files and set the SDL2_DIR environment variable to point at the directory location in the same way as the previous example. Also make sure that SDL2.dll is in a folder your path. Either 32-bit or 64-bit versions appear to work fine.

As of Visual Studio 2017 it isn't necessary to explicitly generate a solution with CMake. Instead, opening the RoboNeko folder in Visual Studio 2017 will automatically create a project based on the CMake settings and allow you to build and debug from the IDE.

Alternatively using CMake from the command line to create a 32-bit solution:
 
    cd RoboNeko
    mkdir build
    cd build
    cmake ..
	 
or 64-bit solution:

    cd RoboNeko
    mkdir build
    cd build
    cmake -A x64 ..
