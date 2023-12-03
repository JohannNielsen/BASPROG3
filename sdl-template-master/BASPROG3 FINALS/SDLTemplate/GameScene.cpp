#include "GameScene.h"
#include"Player.h"

GameScene::GameScene()
{
	//grid background
	grid = new Grid();
	this->addGameObject(grid);

	player = new Player();
	this->addGameObject(player);

	for (int i = 0; i < 10; i++)
	{
		int position = 18 + (i * 72);
		foodPositionX[i] = position;
	}
	for (int i = 0; i < 10; i++)
	{
		int position = 18 + (i * 72);
		foodPositionY[i] = position;
	}
}

GameScene::~GameScene()
{
	delete player;
}

void GameScene::start()
{
	Scene::start();
	initFonts();

	score = 0;

	spawnFood();
}

void GameScene::draw()
{
	Scene::draw();

	if(player->getIsAlive() == true)
	{
		drawText(125, 5, 255, 255, 255, TEXT_CENTER, "POINTS : %03d", score);
	}
	else
	{
		drawText(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2 + 30, 255, 255, 255, TEXT_CENTER, "YOUR SCORE IS: %03d", score);
	}
	if (player->getIsAlive() == false)
	{
		drawText(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2, 255, 255, 255, TEXT_CENTER, "GAME OVER!");
	}
}

void GameScene::update()
{
	Scene::update();
	Collision();
	if (foodEaten == true)
	{
			spawnFood();
	}
	
}

void GameScene::spawnFood()
{
	Food* food = new Food();
	this->addGameObject(food);

	foodPosX = foodPositionX[rand() % 10];
	foodPosY = foodPositionY[rand() % 10];

	food->setPosition(foodPosX, foodPosY);
	spawnedFood.push_back(food);
	foodEaten = false;
}

void GameScene::despawnFood(Food* food)
{
	int index = 0;

	for (int i = 0; i < spawnedFood.size(); i++)
	{
		if (food == spawnedFood[i])
		{
			index = i;
			break;
		}
	}

	if (index != -1)
	{
		spawnedFood.erase(spawnedFood.begin() + index);
		delete food;
	}
}

void GameScene::Collision()
{
	for (int i = 0; i < objects.size(); i++)
	{
		Food* food = dynamic_cast<Food*>(objects[i]);
		if (food != NULL)
		{
			Food* activeFood = spawnedFood[0];
			if (activeFood->getPositionX() == player->getPositionX() + 18 && activeFood->getPositionY() == player->getPositionY() + 18)
			{
				despawnFood(activeFood);
				foodEaten = true;
				score++;
				player->addBody(1000, 720);
				break;
			}
		}
		if (player->getIsAlive() == true)
		{
			if (player->getPositionX() < 0 || player->getPositionX() >= SCREEN_WIDTH || player->getPositionY() < 0 || player->getPositionY() >= 720)
			{
				player->doDeath();
			}
		}
	}
}