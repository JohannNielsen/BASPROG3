#include "Food.h"

void Food::start()
{
	x = 0;
	y = 0;
	width = 0;
	height = 0;

	foodTexture = loadTexture("gfx/SnakeFood.png");
}

void Food::update()
{
}

void Food::draw()
{
	blit(foodTexture, x, y);
}

int Food::getPositionX()
{
	return x;
}

int Food::getPositionY()
{
	return y;
}

int Food::getWidth()
{
	return width;
}

int Food::getHeight()
{
	return height;
}

void Food::setPosition(int xPos, int yPos)
{
	this->x = xPos;
	this->y = yPos;
}