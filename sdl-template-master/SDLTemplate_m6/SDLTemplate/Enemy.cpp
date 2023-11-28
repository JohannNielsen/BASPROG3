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
	texture2 = loadTexture("gfx/explosion.png");

	directionY = 1;
	width = 0;
	height = 0;
	speed = 1;
	reloadTime = 60;
	currentReloadTime = 0;
	directionChangeTime = (rand() % 240) + 120;
	currentDirectionChangeTime = 0;

	SDL_QueryTexture(texture, NULL, NULL, &width, &height);

	sound = SoundManager::loadSound("sound/334227__jradcoolness__laser.ogg");
	sound->volume = 32;
}

void Enemy::update()
{
	//movement of enemies
	x += directionX * (speed * 2);
	y += directionY * speed;

	//timer for the changing of direction every specific amount of seconds
	if (currentDirectionChangeTime > 0)
		currentDirectionChangeTime--;
	// direction change if the enemy is on the border of the screen
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

	//reload timer for enemies
	if (currentReloadTime > 0)
	{
		currentReloadTime--;
	}

	if (currentReloadTime == 0)
	{
		float dx = -1;
		float dy = 0;
		//finding player position
		calcSlope(playerTarget->getPositionX(), playerTarget->getPositionY(), x, y, &dx, &dy);

		SoundManager::playSound(sound);
		Bullet* bullet = new Bullet(x + 14 / 2, y  + height / 2, dx, dy, (rand() % 7) + 5, Side::ENEMY_SIDE);

		bullets.push_back(bullet);
		getScene()->addGameObject(bullet);

		currentReloadTime = reloadTime;
	}
	// despawn bullets
	for (int i = 0; i < bullets.size(); i++)
	{
		if (bullets[i]->getPositionY() > SCREEN_HEIGHT || bullets[i]->getPositionX() > SCREEN_WIDTH
			|| bullets[i]->getPositionX() < -100 || bullets[i]->getPositionY() < -100)
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

void Enemy::setDirectionX(int xDir)
{
	this->directionX = xDir;
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