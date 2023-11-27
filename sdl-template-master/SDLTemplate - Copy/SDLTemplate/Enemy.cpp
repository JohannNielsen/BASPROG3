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
	texture = loadTexture("gfx/enemy.png");

	directionX = -1;
	directionY = 1;
	width = 0;
	height = 0;
	speed = 2;
	reloadTime = 60;
	currentReloadTime = 0;
	directionChangeTime = (rand() % 240) + 120;
	currentDirectionChangeTime = 0;
	

	SDL_QueryTexture(texture, NULL, NULL, &width, &height);

	sound = SoundManager::loadSound("sound/334227__jradcoolness__laser.ogg");
	sound->volume = 64;
}

void Enemy::update()
{
	x += directionX * (speed * 2);
	y += directionY * speed;

	if (currentDirectionChangeTime > 0)
		currentDirectionChangeTime--;

	if (x < 0)
	{
		directionX = -directionX;
	}
	else if (x > SCREEN_WIDTH)
	{
		directionX = -directionX;
	}

	if (currentDirectionChangeTime == 0)
	{
		
		directionX = -directionX;
		
		currentDirectionChangeTime = directionChangeTime;
	}

	if (currentReloadTime > 0)
	{
		currentReloadTime--;
	}

	if (currentReloadTime == 0)
	{
		float dx = -1;
		float dy = 0;

		calcSlope(playerTarget->getPositionX(), playerTarget->getPositionY(), x, y, &dx, &dy);

		SoundManager::playSound(sound);
		Bullet* bullet = new Bullet(x + width, y - 2 + height / 2, dx, dy, 10, Side::ENEMY_SIDE);

		bullets.push_back(bullet);
		getScene()->addGameObject(bullet);

		currentReloadTime = reloadTime;
	}

	for (int i = 0; i < bullets.size(); i++)
	{
		if (bullets[i]->getPositionY() > SCREEN_HEIGHT)
		{
			Bullet* bulletToErase = bullets[i];
			bullets.erase(bullets.begin() + i);
			delete bulletToErase;

			break;
		}


	}
}

void Enemy::draw()
{
	blitRotate(texture, x, y, 270);
}

void Enemy::setPlayerTarget(Player* player)
{
	playerTarget = player;
}

void Enemy::setPosition(int xPos, int yPos)
{
	this->x = xPos;
	this->y = yPos;
}

int Enemy::getPositionX()
{
	return x;
}

int Enemy::getPositionY()
{
	return y;
}

int Enemy::getWidth()
{
	return width;
}

int Enemy::getHeight()
{
	return height;
}