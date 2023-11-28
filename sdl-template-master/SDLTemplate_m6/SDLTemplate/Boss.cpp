#include "Boss.h"
#include "Scene.h"

Boss::Boss()
{
}

Boss::~Boss()
{
}

void Boss::start()
{
	texture = loadTexture("gfx/boss.png");

	directionX = -1;
	directionY = 1;
	x = SCREEN_WIDTH / 2;
	y = -100;

	width = 0;
	height = 0;
	speed = 2;

	reloadTime = 5;
	currentReloadTime = 0;
	currentDirectionChangeTime = 0;
	reloadTime2 = 15;
	currentReloadTime2 = 0;
	reloadTime3 = 600;
	currentReloadTime3 = 0;
	reloadTime4 = 100;
	currentReloadTime4 = 0;
	timer = 180;

	SDL_QueryTexture(texture, NULL, NULL, &width, &height);
	sound = SoundManager::loadSound("sound/334227__jradcoolness__laser.ogg");
	sound->volume = 64;
}

void Boss::update()
{

	int patternCounter = 0;

	srand(time(NULL));
	if (timer > 0)
	{
		y += 1;
		timer--;
	}
	if (timer == 0)
	{
		x += directionX * speed;
	}

	if (x < 0)
	{
		directionX = -directionX;
	}
	else if (x >= SCREEN_WIDTH - 10)
	{
		directionX = -directionX;
	}

	if (currentDirectionChangeTime > 0)
		currentDirectionChangeTime--;

	if (currentDirectionChangeTime == 0)
	{
		directionX = -directionX;
		directionChangeTime = (rand() % 480) + 240;
		currentDirectionChangeTime = directionChangeTime;
	}

	// 1st timer
	if (currentReloadTime > 0)
	{
		currentReloadTime--;
	}

	// 2nd timer
	if (currentReloadTime2 > 0)
	{
		currentReloadTime2--;
	}

	// 3rd timer
	if (currentReloadTime3 > 0)
	{
		currentReloadTime3--;
	}

	// 4th timer
	if (currentReloadTime4 > 0)
	{
		currentReloadTime4--;
	}

	// 1st pattern
	if (timer == 0)
	{
		if (currentReloadTime == 0 && currentReloadTime3 > 300 && currentReloadTime3 < 520)
		{
			SoundManager::playSound(sound);
			createMultipleBullet();
			currentReloadTime = reloadTime;
		}

		// 2nd pattern
		if (currentReloadTime3 == 0)
		{
			SoundManager::playSound(sound);
			createSpreadBullet();
			currentReloadTime3 = reloadTime3;
		}

		// 3rd pattern
		if (currentReloadTime2 == 0 && currentReloadTime3 > 0 && currentReloadTime3 < 240)
		{
			SoundManager::playSound(sound);
			createTargetBullet();
			currentReloadTime2 = reloadTime2;
		}

		// 4th pattern
		if (currentReloadTime4 == 0 && patternCounter % 2 == 0)
		{
			SoundManager::playSound(sound);
			createBurstBullet();
			currentReloadTime4 = reloadTime4;
		}
		patternCounter++; 
	}
	// despawn bullets
	for (int i = 0; i < bullets.size(); i++)
	{
		if (bullets[i]->getPositionY() > SCREEN_HEIGHT || bullets[i]->getPositionX() > SCREEN_WIDTH
			|| bullets[i]->getPositionX() < -100 || bullets[i]->getPositionY() < 0)
		{
			Bullet* bulletToErase = bullets[i];
			bullets.erase(bullets.begin() + i);

			delete bulletToErase;

			break;
		}
	}
}

void Boss::draw()
{
	blitRotate(texture, x, y, 180);
}

void Boss::setPlayerTarget(Player* player)
{
	playerTarget = player;
}

int Boss::getPositionX()
{
	return x;
}

int Boss::getPositionY()
{
	return y;
}

int Boss::getWidth()
{
	return width;
}

int Boss::getHeight()
{
	return height;
}

// 1st pattern logic
void Boss::createMultipleBullet()
{

	for (float i = 0; i < 6; i++)
	{
		Bullet* bullet = new Bullet(x + width / 2, y + height - 25, i + .50, 1, 10, Side::ENEMY_SIDE);
		bullets.push_back(bullet);
		getScene()->addGameObject(bullet);
	}
	for (float i = -6; i < 0; i++)
	{
		Bullet* bullet = new Bullet(x + width / 2, y + height - 25, i + .50, 1, 10, Side::ENEMY_SIDE);
		bullets.push_back(bullet);
		getScene()->addGameObject(bullet);
	}
}

// second pattern logic
void Boss::createTargetBullet()
{
	float dx = -1;
	float dy = 0;

	calcSlope(playerTarget->getPositionX(), playerTarget->getPositionY(), x, y, &dx, &dy);

	Bullet* bullet = new Bullet(x + width / 2, y + height - 50, dx, dy, 4, Side::ENEMY_SIDE);
	bullets.push_back(bullet);
	getScene()->addGameObject(bullet);
}

// 3rd pattern logic
void Boss::createSpreadBullet()
{
	float temp = -1;

	for (float i = 0; i < 9; i++)
	{
		temp += .30f;
		Bullet* bullet = new Bullet(x + width / 2, y + height - 50, temp, 1, 10, Side::ENEMY_SIDE);
		bullets.push_back(bullet);
		getScene()->addGameObject(bullet);
	}
}

//4th pattern logic 
void Boss::createBurstBullet()
{
	float nozzleDistance = 150;// Distance between the two nozzles
	float bulletSpeed = 2; // Speed of the bullets
	int bulletCount = 3; // Number of bullets in the burst

	float dx = -1;
	float dy = 0;

	calcSlope(playerTarget->getPositionX(), playerTarget->getPositionY(), x, y, &dx, &dy);

	// first nozzle
	for (int i = 3; i < bulletCount; i++)
	{
		float bulletDirection = -1 + i ;
		Bullet* bullet = new Bullet(x + width, y + height - 50, dx, dy, 4, Side::ENEMY_SIDE);
		bullets.push_back(bullet);
		getScene()->addGameObject(bullet);
	}

	// second nozzle
	
	for (int i = 3; i < bulletCount; i++)
	{
		float bulletDirection = -1 + i ;
		Bullet* bullet = new Bullet(x + width * 2, y + height - 50, dx, dy, 4, Side::ENEMY_SIDE);
		bullets.push_back(bullet);
		getScene()->addGameObject(bullet);
	}
}