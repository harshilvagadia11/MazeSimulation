#ifndef MAIN_H
#define MAIN_H
#pragma once

#define BX 6
#define BY 6
#define GAP 40

#define WALL_THICKNESS 3

#define MAZEX 20
#define MAZEY 20

#define TEXT_GAP 10

#include <bits/stdc++.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_net.h>
#include <SDL2/SDL_mixer.h>

const int SCREEN_WIDTH = 2*BX + MAZEX*GAP;
const int SCREEN_HEIGHT = 2*BY + MAZEY*GAP + 2*TEXT_GAP;

#include "Maze.h"
#include "Texture.h"
#include "Timer.h"
#include "Droid.h"

#endif