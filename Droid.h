#ifndef DROID_H
#define DROID_H
#pragma once
#include "Main.h"

class Texture;
class Droid {
public:
    Droid();
    void insert(int f);
    void move(std::map<std::pair<int,int>,int> &status);
    void move1(std::map<std::pair<int,int>,int> &status);
    void render(SDL_Renderer *gRenderer, Texture &gDroidTexture);
    bool bipartite;
    bool done;

private:
    std::queue<int> buffer;
    int posX, posY;
    int nextX, nextY;
    int face;
    bool found;
    bool yellow;
};

#endif