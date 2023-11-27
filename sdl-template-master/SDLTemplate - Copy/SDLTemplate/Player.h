#pragma once
#include "GameObject.h"
#include "common.h"
#include "draw.h"
#include "SoundManager.h"
#include "Bullet.h"
#include <vector>

class Player : public GameObject
{
public:
    ~Player();
    void start();
    void update();
    void draw();

    int getPositionX();
    int getPositionY();

    int getWidth();
    int  getHeight();

    bool getIsAlive();
    void doDeath();
private:
    SDL_Texture* texture;
    Mix_Chunk* sound;
    SDL_Texture* deathTexture;
    Mix_Chunk* deathSound;
    int x;
    int y;
    int width;
    int height;
    int speed;
    float reloadTime;
    float currentReloadTime;

    float soundTimer;
    float soundResetTime;

    float deathAnimationFrames;
    std::vector<Bullet*> bullets;
    
    bool isAlive;
};

