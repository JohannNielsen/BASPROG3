#pragma once
#include "GameObject.h"
#include "common.h"
#include "draw.h"
#include "util.h"

class Food :
    public GameObject
{
public:
    void start();
    void update();
    void draw();
    int getPositionX();
    int getPositionY();
    int getWidth();
    int getHeight();
    void setPosition(int xPos, int yPos);

private:
    SDL_Texture* foodTexture;
    int x;
    int y;
    int width;
    int height;
};