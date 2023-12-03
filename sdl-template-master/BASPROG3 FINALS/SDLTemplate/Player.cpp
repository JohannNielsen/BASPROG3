#include "Player.h"
#include "Scene.h"
#include"GameScene.h"

void Player::start()
{
	texture = loadTexture("gfx/SnakeHead.png");
	texture2 = loadTexture("gfx/SnakeBody.png");

	width = 0;
	height = 0;
	speed = 72;
	isMoving = false;
	isAlive = true;
	addBody(0, 0);


	currentDirectionChangeTimer = 18;
	directionChangeTimer = 18;

	SDL_QueryTexture(texture, NULL, NULL, &width, &height);

}

void Player::update()
{
	//if (!isAlive) return;

	if (app.keyboard[SDL_SCANCODE_W])
	{
		if (dirY == 0)
		{
			dirX = 0;
			dirY = -1;
		}
	}

	if (app.keyboard[SDL_SCANCODE_S])
	{
		if (dirY == 0)
		{
			dirX = 0;
			dirY = 1;
		}
	}

	if (app.keyboard[SDL_SCANCODE_SPACE])
	{
		bodyPart.clear();
		start();
		isAlive = true;
	}

	if (app.keyboard[SDL_SCANCODE_A])
	{
		if (dirX == 0)
		{
			dirX = -1;
			dirY = 0;
		}
	}

	if (app.keyboard[SDL_SCANCODE_D])
	{
		if (dirX == 0)
		{
			dirX = 1;
			dirY = 0;
		}
	}

	if (currentDirectionChangeTimer > 0)
		currentDirectionChangeTimer--;

	if (currentDirectionChangeTimer == 0)
	{
		if (isMoving == true) {
			for (int i = bodyPart.size() - 1; i > 0; i--)
			{
				bodyPart[i].x = bodyPart[i - 1].x;
				bodyPart[i].y = bodyPart[i - 1].y;
			}
			isMoving = false;
		}
		currentDirectionChangeTimer = directionChangeTimer;
		if (dirX == 1)
		{
			bodyPart[0].x = bodyPart[0].x + (speed % 144);
		}
		if (dirX == -1)
		{
			bodyPart[0].x = bodyPart[0].x - (speed % 144);
		}
		if (dirY == 1)
		{
			bodyPart[0].y = bodyPart[0].y + (speed % 144);
		}
		if (dirY == -1)
		{
			bodyPart[0].y = bodyPart[0].y - (speed % 144);
		}

		isMoving = true;
	}

	for (int i = 1; i < bodyPart.size(); i++)
	{
		if (bodyPart[0].x == bodyPart[i].x && bodyPart[0].y == bodyPart[i].y)
		{
			isAlive = false;
		}
	}
}

void Player::draw()
{
	if (!isAlive)
		return;
	for (int i = 0; i < bodyPart.size(); i++)
	{
		if (i == 0)
		{
			if (dirX == 1)
			{
				blit(texture, bodyPart[i].x, bodyPart[i].y);
			}
			if (dirX == -1)
			{
				blitRotate(texture, bodyPart[i].x, bodyPart[i].y, 180);
			}
			if (dirY == 1)
			{
				blitRotate(texture, bodyPart[i].x, bodyPart[i].y, 90);
			}
			if (dirY == -1)
			{
				blitRotate(texture, bodyPart[i].x, bodyPart[i].y, -90);
			}
		}
		else
		{
			if (dirX == 1)
			{
				blit(texture2, bodyPart[i].x, bodyPart[i].y);
			}
			if (dirX == -1)
			{
				blitRotate(texture2, bodyPart[i].x, bodyPart[i].y, 180);
			}
			if (dirY == 1)
			{
				blitRotate(texture2, bodyPart[i].x, bodyPart[i].y, 90);
			}
			if (dirY == -1)
			{
				blitRotate(texture2, bodyPart[i].x, bodyPart[i].y, -90);
			}
		}
	}
}

void Player::addBody(int x, int y)
{
	snakeBody part;
	part.x = x;
	part.y = y;
	bodyPart.push_back(part);
}

bool Player::getIsAlive()
{
	return isAlive;
}

void Player::setIsAlive(bool a)
{
	this->isAlive = a;
}

void Player::doDeath()
{
	isAlive = false;
}

int Player::getPositionX()
{
	return bodyPart[0].x;
}

int Player::getPositionY()
{
	return bodyPart[0].y;
}