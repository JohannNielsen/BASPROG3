#include "PowerUp.h"

PowerUp::PowerUp(float PositionX, float PositionY, float directionX, float directionY, float speed)
{
	this->x = PositionX;
	this->y = PositionY;
	this->directionX = directionX;
	this->directionY = directionY;
	this->speed = speed;
}

void PowerUp::start()
{
	texture = loadTexture("gfx/points.png");

	width = 0;
	height = 0;
	powerUpLevel = 1;
	SDL_QueryTexture(texture, NULL, NULL, &width, &height);
}

void PowerUp::update()
{
	x += directionX * speed;
	y += directionY * speed;
}

void PowerUp::draw()
{
	blit(texture, x, y);
}

int PowerUp::getPositionX()
{
	return x;
}

int PowerUp::getPositionY()
{
	return y;
}

int PowerUp::getWidth()
{
	return width;
}

int PowerUp::getHeight()
{
	return height;
}

int PowerUp::getPowerUpLevel()
{
	return powerUpLevel;
}