#include "Player.h"
#include "Scene.h"



Player::~Player()
{
	for (int i = 0; i < bullets.size(); i++)
	{
		delete bullets[i];
	}

	bullets.clear();
}

void Player::start()
{
	texture = loadTexture("gfx/player.png");

	x = SCREEN_WIDTH / 2;
	y = SCREEN_HEIGHT / 2 + 200;
	width = 0;
	height = 0;
	speed = 5;
	reloadTime = 8;
	currentReloadTime = 0;
	isAlive = true;

	SDL_QueryTexture(texture, NULL, NULL, &width, &height);

	sound = SoundManager::loadSound("sound/334227__jradcoolness__laser.ogg");
}

void Player::update()
{
	int directionX = 0;
	int directionY = -1;
	for (int i = 0; i < bullets.size(); i++)
	{
		if (bullets[i]->getPositionY() < 0)
		{
			Bullet* bulletToErase = bullets[i];
			bullets.erase(bullets.begin() + i);
			delete bulletToErase;

			break;
		}
	}


	if (!isAlive) return;

	if (app.keyboard[SDL_SCANCODE_W])
	{
		y -= speed;
	}
	if (app.keyboard[SDL_SCANCODE_S])
	{
		y += speed;
	}
	if (app.keyboard[SDL_SCANCODE_A])
	{
		x -= speed;
	}
	if (app.keyboard[SDL_SCANCODE_D])
	{
		x += speed;
	}

	if (currentReloadTime > 0)
	{
		currentReloadTime--;
	}

	if (app.keyboard[SDL_SCANCODE_F] && currentReloadTime <= 0)
	{
		SoundManager::playSound(sound);

		createBullet();

		currentReloadTime = reloadTime;
	}

	
}

void Player::draw()
{
	if (!isAlive) return;

	blitRotate(texture, x, y, 270);
	
}

void Player::createBullet()
{
	Bullet* bullet = new Bullet(x - 12 + width / 2, y, 0, -1, 10, Side::PLAYER_SIDE);
	Bullet* bullet2 = new Bullet(x - 12 + width / 2, y, 0.25, -1, 10, Side::PLAYER_SIDE);
	Bullet* bullet3 = new Bullet(x - 12 + width / 2, y, -0.25, -1, 10, Side::PLAYER_SIDE);
	Bullet* bullet4 = new Bullet(x - 12 + width / 2, y, 0.50, -1, 10, Side::PLAYER_SIDE);
	Bullet* bullet5 = new Bullet(x - 12 + width / 2, y, -0.50, -1, 10, Side::PLAYER_SIDE);

	bullets.push_back(bullet);
	bullets.push_back(bullet2);
	bullets.push_back(bullet3);
	bullets.push_back(bullet4);
	bullets.push_back(bullet5);


	if (PowerUpLevel == 0)
	{
		getScene()->addGameObject(bullet);
	}
	else if (PowerUpLevel == 1)
	{
		getScene()->addGameObject(bullet2);
		getScene()->addGameObject(bullet3);

	}
	else if (PowerUpLevel == 2)
	{
		getScene()->addGameObject(bullet);
		getScene()->addGameObject(bullet2);
		getScene()->addGameObject(bullet3);
	}
	else if (PowerUpLevel == 3)
	{
		getScene()->addGameObject(bullet2);
		getScene()->addGameObject(bullet3);
		getScene()->addGameObject(bullet4);
		getScene()->addGameObject(bullet5);
	}
	else
	{
		getScene()->addGameObject(bullet);
		getScene()->addGameObject(bullet2);
		getScene()->addGameObject(bullet3);
		getScene()->addGameObject(bullet4);
		getScene()->addGameObject(bullet5);
	}
}

int Player::getPositionX()
{
	return x;
}

int Player::getPositionY()
{
	return y;
}

int Player::getWidth()
{
	return width;
}

int Player::getHeight()
{
	return height;
}

bool Player::getIsAlive()
{
	return isAlive;
}

void Player::doDeath()
{
	isAlive = false;
}

void Player::settempPowerUpLevel(int level)
{
	PowerUpLevel = level;
}
