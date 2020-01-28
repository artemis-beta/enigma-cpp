# Enigma UI Version

This application is Qt GUI version of the Enigma Simulation coded in C++ (the full version is found on branch `master`). Currently the included `build.sh` script is set to compile and build a Mac OS X application with a view to expanding this to Linux and Windows in the futurei.A
Building requires the [C++ boost library](https://www.boost.org/), the script should be modified to point to the location of this library if it is not in the default location of `/usr/loca/opt/boost/include/`. Also important is to ensure that the `CMakeLists.txt` is properly configured to point to your install of Qt5 by correctly setting the `Qt5_DIR` variable.
