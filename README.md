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

Set the SDL2_DIR variable in the CMakeLists.txt to point to the SDL 2.0.9 development files. The following commands assume the CMD interpreter.

#### Code::Blocks

From within the source directory, create a build folder and optionally specify the CMAKE_BUILD_TYPE:

    git clone https://github.com/nspool/RoboNeko.git
    cd RoboNeko & mkdir build & cd build
    cmake -G "CodeBlocks" -DCMAKE_BUILD_TYPE=Debug  ..

Then open RoboNeko.cbp in the Code::Blocks IDE.

#### Visual Studio

As of Visual Studio 2017 it isn't necessary to explicitly generate a solution with CMake. Instead, opening the RoboNeko folder in Visual Studio 2017 will automatically create a project based on the CMake settings and allow you to build and debug from the IDE.

Alternatively using CMake from the Visual Studio command line to create a 32-bit solution:
 
    git clone https://github.com/nspool/RoboNeko.git
    cd RoboNeko & mkdir build & cd build
    cmake ..
	 
or 64-bit solution:

    git clone https://github.com/nspool/RoboNeko.git
    cd RoboNeko & mkdir build & cd build
    cmake -A x64 ..
