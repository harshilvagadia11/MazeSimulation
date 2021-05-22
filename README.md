# MazeSimulation
A DFS visualiser on a maze. This visualiser shows the path traced by DFS algorithm via movement of a tank on a maze.
The speed of the tank can be adjusted and the simulation can be paused. We also colour code the nodes that are visited.

## Dependencies
Open terminal and run the following commands to install the dependencies:
### Ubuntu
1. `sudo apt install g++`
2. `sudo apt-get install -libsdl2-dev`
3. `sudo apt-get install -libsdl2-ttf-dev`
4. `sudo apt-get install -libsdl2-net-dev`
5. `sudo apt-get install -libsdl2-mixer-dev`
6. `sudo apt-get install npm`

### MacOS
1. `brew install sdl2 sdl2_ttf sdl2_net sdl2_mixer npm`

# Compilation
Run `make` to compile the program.

# Execution
Run `./simulate` to execute the simulation. The simulation can be paused and unpaused by pressing space bar. The speed can be increased or decreased by usinf left and right arrow keys.
