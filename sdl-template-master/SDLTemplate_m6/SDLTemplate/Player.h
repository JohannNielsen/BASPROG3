#pragma once
#include "GameObject.h"
#include "common.h"
#include "draw.h"
#include "SoundManager.h"
#include "Bullet.h"
#include <vector>


class Player :
	public GameObject
{
public:
	~Player();

	void start();
	void update();
	void draw();

	void createBullet();
	int getPositionX();
	int getPositionY();
	int getWidth();
	int getHeight();

	bool getIsAlive();
	void doDeath();

	void settempPowerUpLevel(int level);

private:
	SDL_Texture* texture;
	Mix_Chunk* sound;
	Mix_Chunk* sound2;

	int x;
	int y;
	int width;
	int height;
	int speed;
	float reloadTime;
	float currentReloadTime;
	int PowerUpLevel;

	std::vector<Bullet*> bullets;

	bool isAlive;
};