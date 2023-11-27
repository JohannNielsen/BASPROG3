#pragma once
#include "GameObject.h"
#include "common.h"
#include "draw.h"

class PowerUp :
	public GameObject
{
public:
	PowerUp(float PositionX, float PositionY, float directionX, float directionY, float speed);

	void start();
	void update();
	void draw();

	int getPositionX();
	int getPositionY();
	int getWidth();
	int getHeight();
	int getPowerUpLevel();

private:
	SDL_Texture* texture;

	int x;
	int y;
	int width;
	int height;
	int speed;
	float directionX;
	float directionY;
	int powerUpLevel;
};