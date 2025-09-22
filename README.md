# Tetris
Tetris classic clone written in C++ suing SDL2

## Build and run
The project contains prebuilt binaries for Windows 10 and Archlinux, try running them, otherwise build the source code as instructed.
### Linux
Run cmake and build with make
```bash
cd linux-build
cmake ..
make
```
### Windows
Try using cmake with the config file provided
```cmd
cd windows-build
cmake ..
make
```
If cmake can't find the SDL2 package, try compiling with the Makefile provided, but first make sure the library paths and version are set correctly
```Makefile
EXTERNLIBPATH		="C:/Program Files/SDL2-2.0.22/x86_64-w64-mingw32"
SDL2_IMAGE_PATH		="C:/Program Files/SDL2_image"
SDL2_TTF_PATH       ="C:/Program Files/SDL2_ttf"
```
once paths are set, copy the Makefile provided, and run make
```cmd
copy Makefile windows-build/Makefile
cd windows-build
make
```

## Tips
The file ```settings.hpp``` found under ```assets/settings.hpp```, but under the build folder ```linux-build``` or ```windows-build``` contains settings for the game. Find the variables and feel free to play around with the values (grid size, screen size, position of objects). Tweaking these values will unfortunately require recompiling as the file is a C++ header.

## Disclaimer
- Contains a couple of bugs (rotation needs better collision checks)
- the graphical design could be better:)
- window not resizable
- ```assets``` folder is stored separately under ```windows/linux``` build folders + another copy at project root. Needed restructuring
