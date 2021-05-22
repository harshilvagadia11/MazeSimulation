# MazeSimulation
A DFS and Bipartite visualiser on a maze. This visualiser shows the path traced by DFS algorithm and Bipartite Graph Algorithm via movement of a tank on a maze.
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
Run `./simulate` to execute the simulation. Select the simulation to be executed by UP,DOWN arrow keys. The simulation can be paused and unpaused by pressing SPACE. The speed can be increased or decreased by using LEFT and RIGHT arrow keys.
