#include "Enemy.h"
#include "Scene.h"

Enemy::Enemy()
{
}

Enemy::~Enemy()
{
}

void Enemy::start()
{
	//load texture
	texture = loadTexture("gfx/enemy.png");

	//initialize value
	directionX = -1;
	directionY = 1;
	width = 0;
	height = 0;
	speed = 2;
	reloadTime = 60;
	currentReloadTime = 0;
	directionChangeTime = (rand() % 300) + 180; //direction change time of 3-8 seconds
	currentDirectionChangeTime = 0;

	//query the texture to set our width and height
	SDL_QueryTexture(texture, NULL, NULL, &width, &height);

	sound = SoundManager::loadSound("sound/334227__jradcoolness__laser.ogg");
}

void Enemy::update()
{
	x += directionX * speed;
	y += directionY * speed;

	if (currentDirectionChangeTime > 0)
	{
		currentDirectionChangeTime--; 
	}

	if (currentDirectionChangeTime == 0)
	{
		directionY = -directionY;
		currentDirectionChangeTime = directionChangeTime;
	}

	if (currentReloadTime > 0)
		currentReloadTime--;

	if (currentReloadTime == 0)
	{
		float dx = -1;
		float dy = 0;

		calcSlope(playerTarget->getPositionX(), playerTarget->getPositionY(), x, y, &dx, &dy);

		SoundManager::playSound(sound);
		Bullet* bullet = new Bullet(x + width, y - 2 + height / 2, dx, dy, 10);
		bullets.push_back(bullet);
		getScene()->addGameObject(bullet);

		//after firing, reset our reload timer
		currentReloadTime = reloadTime;
	}

	//memory manage our bullets. when they go off screen, delete them
	for (int i = 0; i < bullets.size(); i++)
	{
		if (bullets[i]->getPositionX() < 0)
		{
			//Cache the variable so we can delete it later
			// we cant delete it after erasing from the vector (leaked pointer)
			Bullet* bulletToErase = bullets[i];
			bullets.erase(bullets.begin() + i);
			delete bulletToErase;

			//we cant mutate (change) or vector while looping inside it
			//this might crash on the next loop iteration

			//to counter that, we only delete one bullet per frame
			//we can also avoid lag this way
			break;
		}
	}
}

void Enemy::draw()
{
	blit(texture, x, y);
}

void Enemy::SetPlayerTarget(Player* player)
{
	playerTarget = player;
}

void Enemy::setPosition(int x, int y)
{
	this->x = x;
	this->y = y;
}
