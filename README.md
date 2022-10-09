# Space Tetris
Two player vs battle Tetris game

![Tetris image](img/tetris.gif)

[Click here for video](img/tetris.mp4)

## Build
#### Linux

Install CMake, e.g. for Debian/Ubuntu:
```
sudo apt-get install build-essential libssl-dev
sudo apt-get install cmake
```
Install SFML:
```
sudo apt-get install libsfml-dev
```

Clone repo and make a new directory called ```build``` inside the ```src```
directory and enter it.
```
cd {DOWNLOAD_LOCATION}/space-tetris/src
mkdir build
cd build
```
run CMake
```
cmake ../
```

run make
```
make
```
Start the game:
```
./Tetris
```
#### Windows
Install [CMake](https://cmake.org/), use CMake GUI or command line to generate
Visual Studio .sln file, then build with VS.

## Controls
```
Left player:
  Left/Right: A/D
  Rotate : W
  Drop : S

Right player:
  Left/Right: Left/Right arrow keys
  Rotate : Up arrow key
  Drop : Down arrow key

```

![Tetris image](img/tetrisG.png)

set ```GRAPHICS``` to ```OFF``` in CMakeLists.txt for barebones look:

![Tetris image2](img/tetris.png)
