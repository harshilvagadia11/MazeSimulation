#include "Droid.h"

enum direction {left, up, right, down};

Droid::Droid() {
    posX = GAP + BX + 10;
    posY = GAP + BY + TEXT_GAP + 10;
    nextX = posX; nextY = posY;
    face = right;
    found = false;
    yellow=true;
}

void Droid::insert(int f) {
    buffer.push(f);
}

void Droid::move1(std::map<std::pair<int,int>,int> &status) {
    if(posX == nextX && posY == nextY) {
        if(status.find({nextX,nextY}) == status.end()) {
            if (yellow) status[{nextX,nextY}] = 1;
            else status[{nextX,nextY}] = 2;
        }
        yellow=!yellow;
        if(buffer.empty()) return;
        // if((buffer.front() == left && face == right) || (buffer.front() == right && face == left) || (buffer.front() == up && face == down) || (buffer.front() == down && face == up)) {
        //     status[{nextX,nextY}] = 2;
        // }
        face = buffer.front();
        buffer.pop();
        if(face == left) nextX -= GAP;
        else if(face == up) nextY -= GAP;
        else if(face == right) nextX += GAP;
        else nextY += GAP;
    }
    if(posX != nextX || posY != nextY) {
        if(face == left) posX -= 1;
        else if(face == up) posY -= 1;
        else if(face == right) posX += 1;
        else posY += 1;
    }
}

void Droid::move(std::map<std::pair<int,int>,int> &status) {
    if(posX == nextX && posY == nextY) {
        if(status.find({nextX,nextY}) == status.end()) {
            status[{nextX,nextY}] = 1;
        } else status[{nextX,nextY}] = 2;
        if(buffer.empty()) return;
        if((buffer.front() == left && face == right) || (buffer.front() == right && face == left) || (buffer.front() == up && face == down) || (buffer.front() == down && face == up)) {
            status[{nextX,nextY}] = 2;
        }
        face = buffer.front();
        buffer.pop();
        if(face == left) nextX -= GAP;
        else if(face == up) nextY -= GAP;
        else if(face == right) nextX += GAP;
        else nextY += GAP;
    }
    if(posX != nextX || posY != nextY) {
        if(face == left) posX -= 1;
        else if(face == up) posY -= 1;
        else if(face == right) posX += 1;
        else posY += 1;
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