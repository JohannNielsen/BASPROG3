#pragma once
#include "GameObject.h"
#include "common.h"
#include "draw.h"
#include "SoundManager.h"
#include "Bullet.h"
#include <vector>
#include "util.h"
#include "Player.h"

class Enemy : public GameObject
{
public:
    Enemy();
    ~Enemy();
    void start();
    void update();
    void draw();
    void SetPlayerTarget(Player* player);
    void setPosition(int x, int y);
    void deathAnimation();
    void deathAnimationSound();

    int getPositionX();
    int getPositionY();

    int getWidth();
    int getHeight();

private:
    SDL_Texture* texture;
    Mix_Chunk* sound;
    SDL_Texture* deathTexture;
    Mix_Chunk* deathSound;

    Player* playerTarget;
    int x;
    int y;
    float directionX;
    float directionY;
    int width;
    int height;
    int speed;
    float reloadTime;
    float currentReloadTime;
    float directionChangeTime;
    float currentDirectionChangeTime;
    float deathAnimationFrames;

    float soundTimer;
    float soundResetTime;
    std::vector<Bullet*> bullets;

    bool isAlive;
};

