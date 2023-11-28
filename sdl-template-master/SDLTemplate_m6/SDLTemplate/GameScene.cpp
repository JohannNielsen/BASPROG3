#include "GameScene.h"



GameScene::GameScene()
{
	// Register and add game objects on constructor

	createBackGround();

	player = new Player();
	this->addGameObject(player);

	points = 0;
	powerUpCount = 0;
	wave = 0;
	numWaves = 5;
	level = 1;

	bossStat = 0;
	bossHp = 1000;
	bossHpAdd = bossHp;
}

GameScene::~GameScene()
{
	delete player;
	delete background;
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

	bossSpawnTimer = 300;
	bossTimerReset = bossSpawnTimer;
	textTimer = 240;
	timer = 60;

	sound1 = SoundManager::loadSound("sound/245372__quaker540__hq-explosion.ogg");
	sound2 = SoundManager::loadSound("sound/342749__rhodesmas__notification-01.ogg");
	sound1->volume = 5;
	sound2->volume = 30;
}

void GameScene::draw()
{
	Scene::draw();


	if (player->getIsAlive() == true)
	{
		drawText(165, 20, 255, 255, 255, TEXT_CENTER, "NUM OF WAVES: %03d", numWaves);
		drawText(95, 50, 255, 255, 255, TEXT_CENTER, "WAVE: %03d", wave);
		drawText(SCREEN_WIDTH -150, 20, 255, 255, 255, TEXT_CENTER, "POINTS: %03d", points);
		drawText(SCREEN_WIDTH -	150, 50, 255, 255, 255, TEXT_CENTER, "LEVEL: %03d", level);
	}
	else
	{
		drawText(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2 + 30, 255, 255, 255, TEXT_CENTER, "SCORE:");
		drawText(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2 + 60, 255, 255, 255, TEXT_CENTER, "POINTS: %03d", points);
		drawText(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2 + 90, 255, 255, 255, TEXT_CENTER, "WAVE REACHED: %03d", wave);
		drawText(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2 + 120, 255, 255, 255, TEXT_CENTER, "LEVEL REACHED: %03d", level);

	}
	if (player->getIsAlive() == false)
	{
		drawText(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2, 255, 255, 255, TEXT_CENTER, "GAME OVER!");
	}
	if (bossStat == 1)
	{
		drawText(SCREEN_WIDTH / 2, 200, 255, 255, 255, TEXT_CENTER, "BOSS HEALTH: %03d", bossHp);
		if (textTimer > 0)
		{
			drawText(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2, 255, 255, 255, TEXT_CENTER, "LINES OF FIRE HAS BEEN RESET!");
			textTimer--;
		}
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

// spawn logic of the enemy waves and boss stage
void GameScene::doSpawnLogic()
{
	if (wave < numWaves && player->getIsAlive() == true)
	{
		if (currentSpawnTimer > 0)
			currentSpawnTimer--;

		if (currentSpawnTimer == 0)
		{
			for (int i = 0; i < numWaves; i++)
			{
				spawn();
				currentSpawnTimer = spawnTime;
			}
			wave += 1;
		}
		tempWave = wave;
	}
	else if (tempWave == numWaves)
	{

		if (bossSpawnTimer > 0)
			bossSpawnTimer--;

		if (bossSpawnTimer == 0)
		{
			player->settempPowerUpLevel(0);
			powerUpCount = 0;
			spawnBoss();
			tempWave = 0;
			bossStat = 1;
		}
	}
}
// collision logic for bullets and powerups
void GameScene::doCollisionLogic()
{

	for (int i = 0; i < objects.size(); i++)
	{
		Bullet* bullet = dynamic_cast<Bullet*> (objects[i]);
		PowerUp* powerUps = dynamic_cast<PowerUp*> (objects[i]);

		if (bullet != NULL)
		{
			//player collision
			if (bullet->getSide() == Side::ENEMY_SIDE)
			{
				int collision = checkCollision(
					player->getPositionX(), player->getPositionY(), player->getWidth(), player->getHeight(),
					bullet->getPositionX(), bullet->getPositionY(), bullet->getWidth(), bullet->getHeight()
				);

				if (player->getIsAlive() == true)
				{
					if (collision == 1)
					{
						player->doDeath();
						break;
					}
				}
			}
			else if (bullet->getSide() == Side::PLAYER_SIDE)
			{
				//enemy collision
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

						SoundManager::playSound(sound1);
						points += 100;
						break;
					}
				}
				//boss collision
				if (bossStat == 1)
				{
					int collision = checkCollision(
						boss->getPositionX(), boss->getPositionY(), boss->getWidth(), boss->getHeight(),
						bullet->getPositionX(), bullet->getPositionY(), bullet->getWidth(), bullet->getHeight()
					);
					if (collision == 1)
					{
						bossHp -= 1;
						SoundManager::playSound(sound1);
						sound1->volume = 10;
						if (bossHp == 0)
						{
							SoundManager::playSound(sound1);
							sound1->volume = 70;
							delete boss;
							bossSpawnTimer = bossTimerReset;
							bossStat = 0;
							wave = 0;
							level += 1;
							bossHpAdd *= 2;
							bossHp = bossHpAdd;
							points += 1000;
							numWaves += 1;
						}
					}
				}
			}
		}
		//power up collision
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
					SoundManager::playSound(sound2);
				}
			}
		}
	}
}
// spawn function for enemies
void GameScene::spawn()
{
	int randNum = rand() % 2;
	Enemy* enemy = new Enemy();
	this->addGameObject(enemy);
	enemy->setPlayerTarget(player);

	enemy->setPosition((rand() % SCREEN_WIDTH + 1), -100);
	if (randNum == 0)
	{
		enemy->setDirectionX(1);
	}
	else
	{
		enemy->setDirectionX(-1);
	}

	spawnedEnemies.push_back(enemy);

	currentSpawnTimer = spawnTime;
}
// despawn for enemies
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

// spawn for powerups
void GameScene::spawnPowerUp()
{
	powerUp = new PowerUp(rand() % SCREEN_WIDTH + 1, -100, 0, 1, 2);
	this->addGameObject(powerUp);
	createdPowerUps.push_back(powerUp);
}
// delete objects that passes beyond the screen 
void GameScene::deleteUnseenObjects()
{
	// for powerups
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
	// for enemies
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

// deleting the obtained powerup
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

// spawn logic for powerup
void GameScene::createPowerUps()
{
	if (currentPowerUpTimer > 0)
		currentPowerUpTimer--;

	if (currentPowerUpTimer == 0 && player->getIsAlive() == true)
	{
		spawnPowerUp();
		currentPowerUpTimer = spawnTime;
	}
}
// spawn function for the boss
void GameScene::spawnBoss()
{
	boss = new Boss();
	this->addGameObject(boss);
	boss->setPlayerTarget(player);
}

void GameScene::createBackGround()
{
	background = new Background();
	this->addGameObject(background);
}