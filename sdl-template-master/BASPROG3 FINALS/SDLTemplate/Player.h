#pragma once
#include "GameObject.h"
#include "common.h"
#include "draw.h" 
#include <vector>
#include "GameScene.h"

class Player :
	public GameObject
{
public:
	virtual void start();
	virtual void update();
	virtual void draw();
	void addBody(int x, int y);
	bool getIsAlive();
	void setIsAlive(bool a);
	void doDeath();
	int getPositionX();
	int getPositionY();

private:
	SDL_Texture* texture;
	SDL_Texture* texture2;

	int dirX;
	int dirY;
	int width;
	int height;
	int speed;
	int delayTimer;
	int initialDelayTimer;
	int currentDirectionChangeTimer;
	int directionChangeTimer;
	bool isMoving;
	bool isAlive;

	struct snakeBody
	{
		int x;
		int y;
		int width;
		int height;
	};
	std::vector <snakeBody> bodyPart;
};