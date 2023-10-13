#include "GameScene.h"

GameScene::GameScene()
{
	// Register and add game objects on constructor
	background = new Background();
	this->addGameObject(background);
	
	player = new Player();
	this->addGameObject(player);

	points = 0;
}

GameScene::~GameScene()
{
	delete player;
	delete background;
}
 
void GameScene::start()
{
	bool isAlive = true;

	Scene::start();
	// Initialize any scene logic here
	initFonts();
	
	currentSpawnTimer = 300;
	spawnTime = 300; // spawn time of 5 seconds =  300 /60 fps

	for (int i = 0; i < 3; i++)
	{
		spawn();
	}


}

void GameScene::draw()
{
	Scene::draw();

	drawText(110, 20, 255, 255, 255, TEXT_CENTER, "POINTS: %03d", points);

	if (player->getIsAlive() == false)
	{
		drawText(SCREEN_WIDTH / 2, 600, 255, 255, 255, TEXT_CENTER, "GAME OVER!");
	}
}

void GameScene::update()
{
	Scene::update();

	doSpawnLogic();

	//check for collision
	doCollisionLogic();
}

void GameScene::doSpawnLogic()
{
	if (currentSpawnTimer > 0)
	{
		currentSpawnTimer--;
	}

	if (currentSpawnTimer <= 0)
	{
		for (int i = 0; i < 3; i++)
		{
			spawn();
		}
		currentSpawnTimer = spawnTime;
	}
}

void GameScene::doCollisionLogic()
{
	for (int i = 0; i < objects.size(); i++)
	{
		//cast to bullet
		Bullet* bullet = dynamic_cast<Bullet*>(objects[i]);

		//check if the cast was successful (i.e. objects[i] is a bullet)
		if (bullet != NULL)
		{
			//if the bullet is from the enemy side
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
			//if the bullet is from the Player side
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
						/*std::cout << "Enemy has been hit!" << std::endl;
						break;*/
						
						despawnEnemy(currentEnemy);
						bool isAlive = false;
						
						//VERY IMPORTANT: only despawn one at a time
						// otherwise we might crash due to looping while deleting

						//increment points
						points++;
						break;
					}
				}
			}
		}
	}
}

void GameScene::spawn()
{
	Enemy* enemy = new Enemy();
	this->addGameObject(enemy);
	enemy->SetPlayerTarget(player);

	enemy->setPosition(1280, 300 + (rand() % 300));
	spawnedEnemies.push_back(enemy);
	
}

void GameScene::despawnEnemy(Enemy* enemy)
{
	int index = -1;

	for (int i = 0; i < spawnedEnemies.size(); i++)
	{
		//if the pointer matches
		if (enemy == spawnedEnemies[i])
		{
			index = i;
			enemy->deathAnimation();
			enemy->deathAnimationSound();
			
			break;
		}
	}

	//if any match is found
	if (index != -1)
	{
		spawnedEnemies.erase(spawnedEnemies.begin() + index);
		delete enemy;

	}
}
