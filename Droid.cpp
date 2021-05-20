#include "Droid.h"

enum direction {left, up, right, down};

Droid::Droid() {
    posX = GAP + BX + 10;
    posY = GAP + BY + TEXT_GAP + 10;
    nextX = posX; nextY = posY;
    face = right;
    vel = 0.2, delay = 0.0;
}

void Droid::insert(int f) {
    buffer.push(f);
}

void Droid::move() {
    delay += vel;
    if(delay < 1) return;
    delay--;
    if(posX == nextX && posY == nextY) {
        if(buffer.empty()) return;
        face = buffer.front();
        buffer.pop();
        if(face == left) nextX -= GAP;
        else if(face == up) nextY -= GAP;
        else if(face == right) nextX += GAP;
        else nextY += GAP;
    }
    if(posX != nextX || posY != nextY) {
        if(face == left) posX--;
        else if(face == up) posY--;
        else if(face == right) posX++;
        else posY++;
    }
}

void Droid::render(SDL_Renderer *gRenderer, Texture &gDroidTexture) {
    int degree;
    if(face == up) degree = 0;
    else if(face == right) degree = 90;
    else if(face == down) degree = 180;
    else degree = 270;
	gDroidTexture.render(gRenderer, posX, posY, NULL, degree);
}