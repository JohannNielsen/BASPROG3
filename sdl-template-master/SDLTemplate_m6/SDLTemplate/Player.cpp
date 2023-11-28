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
	reloadTime = 10;
	currentReloadTime = 0;
	isAlive = true;

	SDL_QueryTexture(texture, NULL, NULL, &width, &height);

	sound = SoundManager::loadSound("sound/334227__jradcoolness__laser.ogg");
	sound2 = SoundManager::loadSound("sound/245372__quaker540__hq-explosion.ogg");
	sound->volume = 32;
	sound2->volume = 15;
}

void Player::update()
{
	int directionX = 0;
	int directionY = -1;
	for (int i = 0; i < bullets.size(); i++)
	{
		if (bullets[i]->getPositionY() < 0 || bullets[i]->getPositionX() < -100 || bullets[i]->getPositionX() > SCREEN_WIDTH
			)
		{
			Bullet* bulletToErase = bullets[i];
			bullets.erase(bullets.begin() + i);
			delete bulletToErase;

			break;
		}
	}

	if (!isAlive) return;

	if (x > SCREEN_WIDTH)
	{
		x = -100;
	}
	else if (x < -100)
	{
		x = SCREEN_WIDTH;
	}
	else if (y > SCREEN_HEIGHT)
	{
		y = SCREEN_HEIGHT - 50;
	}
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

	if (PowerUpLevel == 0)
	{
		Bullet* bullet = new Bullet(x - 14 + width / 2, y, 0, -1, 10, Side::PLAYER_SIDE);
		bullets.push_back(bullet);
		getScene()->addGameObject(bullet);
	}
	else if (PowerUpLevel >= 1)
	{
		float temp = 0;
		float temp2 = 0;

		for (int i = 0; i < PowerUpLevel; i++)
		{
			temp += .20;
			Bullet* bullet = new Bullet(x - 14 + width / 2, y, temp, -1, 10, Side::PLAYER_SIDE);
			bullets.push_back(bullet);
			getScene()->addGameObject(bullet);

		}
		for (int i = -PowerUpLevel; i < 0; i++)
		{
			temp2 += .20;
			Bullet* bullet = new Bullet(x - 12 + width / 2, y, -temp2, -1, 10, Side::PLAYER_SIDE);
			bullets.push_back(bullet);
			getScene()->addGameObject(bullet);

		}
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
	SoundManager::playSound(sound2);
}

void Player::settempPowerUpLevel(int level)
{
	PowerUpLevel = level;
}