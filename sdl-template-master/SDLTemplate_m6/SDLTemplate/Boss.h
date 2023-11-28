#pragma once
#include "GameObject.h"
#include "GameObject.h"
#include "common.h"
#include "draw.h"
#include "SoundManager.h"
#include "Bullet.h"
#include <vector>
#include "util.h"
#include "Player.h"

class Boss :
	public GameObject
{
public:
	Boss();
	~Boss();

	void start();
	void update();
	void draw();

	void setPlayerTarget(Player* player);

	int getPositionX();
	int getPositionY();
	int getWidth();
	int getHeight();

private:
	SDL_Texture* texture;
	Mix_Chunk* sound;
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

	float timer;
	float reloadTime2;
	float currentReloadTime2;
	float reloadTime3;
	float currentReloadTime3;
	float reloadTime4;
	float currentReloadTime4;

	std::vector<Bullet*> bullets;

	void createMultipleBullet();
	void createTargetBullet();
	void createSpreadBullet();
	void createBurstBullet();
};