#include "GameScene.h"



GameScene::GameScene()
{
	// Register and add game objects on constructor
	player = new Player();
	this->addGameObject(player);

	points = 0;
	powerUpCount = 0;
}

GameScene::~GameScene()
{
	delete player;
}

void GameScene::start()
{
	Scene::start();
	// Initialize any scene logic here
	initFonts();

	currentSpawnTimer = 300;
	spawnTime = 300;

	currentPowerUpTimer = 300;
	PowerUpTimer = 300;

}

void GameScene::draw()
{
	Scene::draw();

	drawText(110, 20, 255, 255, 255, TEXT_CENTER, "POINTS: %03d", points);

	if (player->getIsAlive() == false)
	{
		drawText(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2, 255, 255, 255, TEXT_CENTER, "GAME OVER!");
	}

}

void GameScene::update()
{
	Scene::update();

	doSpawnLogic();
	doCollisionLogic();

	createPowerUps();
	deleteUnseenObjects();
}


void GameScene::doSpawnLogic()
{
	if (currentSpawnTimer > 0)
		currentSpawnTimer--;

	if (currentSpawnTimer == 0)
	{
		for (int i = 0; i < 3; i++)
		{
			spawn();
			currentSpawnTimer = spawnTime;
		}
	}
}

void GameScene::doCollisionLogic()
{

	for (int i = 0; i < objects.size(); i++)
	{
		Bullet* bullet = dynamic_cast<Bullet*> (objects[i]);
		PowerUp* powerUps = dynamic_cast<PowerUp*> (objects[i]);

		if (bullet != NULL)
		{
			if (bullet->getSide() == Side::ENEMY_SIDE)
			{
				int collision = checkCollision(
					player->getPositionX(), player->getPositionY(), player->getWidth(), player->getHeight(),
					bullet->getPositionX(), bullet->getPositionY(), bullet->getWidth(), bullet->getHeight()
				);

				if (collision == 1)
				{
					player->doDeath();
					break;
				}
			}
			else if (bullet->getSide() == Side::PLAYER_SIDE)
			{
				for (int i = 0; i < spawnedEnemies.size(); i++)
				{
					Enemy* currentEnemy = spawnedEnemies[i];

					int collision = checkCollision(
						currentEnemy->getPositionX(), currentEnemy->getPositionY(), currentEnemy->getWidth(), currentEnemy->getHeight(),
						bullet->getPositionX(), bullet->getPositionY(), bullet->getWidth(), bullet->getHeight()
					);
					if (collision == 1)
					{
						despawnEnemy(currentEnemy);

						points += 100;
						break;
					}
				}
			}
		}
		if (powerUps != NULL)
		{
			for (int i = 0; i < createdPowerUps.size(); i++)
			{
				PowerUp* currentPowerUp = createdPowerUps[i];

				int collision = checkCollision(
					player->getPositionX(), player->getPositionY(), player->getWidth(), player->getHeight(),
					currentPowerUp->getPositionX(), currentPowerUp->getPositionY(), currentPowerUp->getWidth(), currentPowerUp->getHeight()
				);
				if (collision == 1)
				{
					powerUpCount++;
					player->settempPowerUpLevel(powerUpCount);
					deleteClaimedPowerUps(currentPowerUp);
				}
			}
		}
	}
}

void GameScene::spawn()
{
	Enemy* enemy = new Enemy();
	this->addGameObject(enemy);
	enemy->setPlayerTarget(player);

	enemy->setPosition(SCREEN_WIDTH / 2 + (rand() % 200), -100);
	spawnedEnemies.push_back(enemy);

	currentSpawnTimer = spawnTime;

}

void GameScene::despawnEnemy(Enemy* enemy)
{
	int index = -1;
	for (int i = 0; i < spawnedEnemies.size(); i++)
	{
		if (enemy == spawnedEnemies[i])
		{
			index = i;
			break;
		}
	}
	if (index != -1)
	{
		spawnedEnemies.erase(spawnedEnemies.begin() + index);
		delete enemy;
	}
}

void GameScene::spawnPowerUp()
{
	powerUp = new PowerUp(rand() % 719 + 1, -100, 0, 1, 2);
	this->addGameObject(powerUp);
	createdPowerUps.push_back(powerUp);
}

void GameScene::deleteUnseenObjects()
{
	for (int i = 0; i < createdPowerUps.size(); i++)
	{
		if (createdPowerUps[i]->getPositionY() > SCREEN_HEIGHT)
		{
			PowerUp* powerUpsToDelete = createdPowerUps[i];
			createdPowerUps.erase(createdPowerUps.begin() + i);
			delete powerUpsToDelete;
			break;
		}
	}
	for (int i = 0; i < spawnedEnemies.size(); i++)
	{
		if (spawnedEnemies[i]->getPositionY() > SCREEN_HEIGHT)
		{
			Enemy* enemiesToDelete = spawnedEnemies[i];
			spawnedEnemies.erase(spawnedEnemies.begin() + i);
			delete enemiesToDelete;
			break;
		}
	}
}

void GameScene::deleteClaimedPowerUps(PowerUp* powerUp)
{
	int index = -1;
	for (int i = 0; i < createdPowerUps.size(); i++)
	{
		if (powerUp == createdPowerUps[i])
		{
			index = i;
			break;
		}
	}
	if (index != -1)
	{
		createdPowerUps.erase(createdPowerUps.begin() + index);
		delete powerUp;
	}
}

void GameScene::createPowerUps()
{
	if (currentPowerUpTimer > 0)
		currentPowerUpTimer--;

	if (currentPowerUpTimer == 0)
	{
		spawnPowerUp();
		currentPowerUpTimer = spawnTime;
	}
}
