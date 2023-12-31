#include "Player.h"
#include "Scene.h"

Player::~Player()
{
	//memory manage our bullets. Delete all bullets on player death
	for (int i = 0; i < bullets.size(); i++)
	{
		delete bullets[i];
	}
	bullets.clear();
}

void Player::start()
{
	//load texture
	texture = loadTexture("gfx/player.png");
	deathTexture = loadTexture("gfx/explosion.png");

	//initialize value
	x = 100;
	y = 100;
	width = 0;
	height = 0;
	speed = 2;
	reloadTime = 8;
	currentReloadTime = 0;
	isAlive = true;

	soundTimer = 1;
	soundResetTime = 0;

	deathAnimationFrames = 0;

	//query the texture to set our width and height
	SDL_QueryTexture(texture, NULL, NULL, &width, &height);

	sound = SoundManager::loadSound("sound/334227__jradcoolness__laser.ogg");
	deathSound = SoundManager::loadSound("sound/245372__quaker540__hq-explosion.ogg");

}

void Player::update()
{
	//memory manage our bullets. when they go off screen, delete them
	for (int i = 0; i < bullets.size(); i++)
	{
		if (bullets[i]->getPositionX() > SCREEN_WIDTH)
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

	if (!isAlive) return;

	if (app.keyboard[SDL_SCANCODE_W])
	{
		y -= speed;
	}
	if (app.keyboard[SDL_SCANCODE_A])
	{
		x -= speed;
	}
	if (app.keyboard[SDL_SCANCODE_S])
	{
		y += speed;
	}
	if (app.keyboard[SDL_SCANCODE_D])
	{
		x += speed;
	}

	if (app.keyboard[SDL_SCANCODE_LSHIFT])
	{
		speed = 5;
	}
	if (app.keyboard[SDL_SCANCODE_BACKSPACE])
	{
		speed = 2;
	}

	//decrement the players reload timer
	if (currentReloadTime > 0)
		currentReloadTime--;

	if (app.keyboard[SDL_SCANCODE_F] && currentReloadTime == 0)
	{
		SoundManager::playSound(sound);
		Bullet* bullet = new Bullet(x + width, y - 2 +height / 2, 1, 0, 10, Side::PLAYER_SIDE);
		bullets.push_back(bullet);
		getScene() -> addGameObject(bullet);

		//after firing, reset our reload timer
		currentReloadTime = reloadTime;
	}

	if (app.keyboard[SDL_SCANCODE_G] && currentReloadTime == 0)
	{
		int originalReloadTime = reloadTime;

		reloadTime = 16;

		SoundManager::playSound(sound);

		Bullet* bullet1 = new Bullet(x, y , 1, 0, 10, Side::PLAYER_SIDE);
		bullets.push_back(bullet1);
		getScene()->addGameObject(bullet1);

		Bullet* bullet2 = new Bullet(x, y + width, 1, 0, 10, Side::PLAYER_SIDE);
		bullets.push_back(bullet2);
		getScene()->addGameObject(bullet2);

		//after firing, reset our reload timer
		currentReloadTime = reloadTime;

		reloadTime = originalReloadTime;
		
	}
	

	
}

void Player::draw()
{
	if (!isAlive)
	{

		if (deathAnimationFrames == 0)
		{
			blit(deathTexture, x, y);
			deathAnimationFrames = 2;

		}	
		return;
	}
	blit(texture, x, y);
	
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
	if (isAlive) 
	{
		isAlive = false;

		if (soundResetTime == 0) 
		{
			SoundManager::playSound(deathSound);
			soundTimer = 1;
		}
	}
}
