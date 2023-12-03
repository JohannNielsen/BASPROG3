#pragma once
#include "GameObject.h"
#include "draw.h"
#include "common.h"

class Grid :
    public GameObject
{
public:
    void start();
    void update();
    void draw();

private:
    SDL_Texture* backdrop;
    int x;
    int y;
};