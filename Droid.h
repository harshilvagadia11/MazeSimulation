#ifndef DROID_H
#define DROID_H
#pragma once
#include "Main.h"

class Texture;
class Droid {
public:
    Droid();
    void insert(int f);
    void move();
    void render(SDL_Renderer *gRenderer, Texture &gDroidTexture);

private:
    std::queue<int> buffer;
    int posX, posY;
    int nextX, nextY;
    int face;
    float vel, delay;
};

#endif