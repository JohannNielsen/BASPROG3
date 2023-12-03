#pragma once
#include "Scene.h"
#include "GameObject.h"
#include "Player.h"
#include "Grid.h"
#include "Food.h"
#include "text.h"


class GameScene : public Scene
{
public:
	GameScene();
	~GameScene();
	void start();
	void draw();
	void update();

private:
	Player* player;
	Grid* grid;
	bool foodEaten;
	void spawnFood();
	void despawnFood(Food* food);
	void Collision();

	std::vector <Food*> spawnedFood;

	int foodPositionX[20];
	int foodPositionY[20];
	int foodPosX;
	int foodPosY;
	int score;
};