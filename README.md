# Frog game
Simple game written in C using linux ncurses library

## How to install
- Make sure you are on linux system or wsl on windows
- Go to your favourite directory
- ```bash
    git clone https://github.com/j01024/FrogGame
    cd FrogGame

    sudo apt-get install libncurses5-dev libncursesw5-dev
    sudo apt-get install cmake
    cmake --build build
    ```
- Run using ```./build/FrogGame```
- Run with settings ```./build/FrogGame settings.fg``` -> You can rename settings.fg file to whatever you wish


# Roadmap
- [x] Basic user interface: status, playable area, jumping frog, moving cars,
streets (lanes), destination place, colors
- [x] Five or more cars constantly moving and randomly appearing which are
wrapping or bouncing, detection of collisions between frog and cars
- [x] Timer and timing mechanism, cars running at different speeds, frog
jumping within limited time
- [x] 4 Using separate configuration text file with parameters of the game, e.g.,
size and shape of the frog and cars, playing area, number, types and
speed of cars, random seeds, colors, etc
- [x] Implementation requirement: well organized code with own structures
(struct) and functions
- [x] Some cars are disappearing when reaching the border, new random cars
are placed on the street (possible time intervals between)
- [x] There are a few static obstacles (e.g., between street lanes) and the speed
of some cars is changing during the game
- [x] Some cars stop the movement when the frog is close to them
- [x] Some cars are friendly cars and catch the frog and move to the another
place
- [x] Game ranking (think over the concept of points)