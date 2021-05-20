#ifndef MAZE_H
#define MAZE_H
#pragma once
#include "Main.h"

struct cell {
    bool in;
    bool up;
    bool left;
    int prevx, prevy;
};

class Maze {
public:
    Maze();
    void initialise();
    void generate();
    void render(SDL_Renderer* renderer, Uint8 opacity);

private:
    int xsize, ysize;
    cell MAZE[MAZEX][MAZEY];
    int numin;
};
#endif