#pragma once
#include "Scene.h"
#include "GameObject.h"
#include "Player.h"
#include "Enemy.h"
#include <vector>
#include "text.h"
#include "PowerUp.h"

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
	Enemy* enemy;
	PowerUp* powerUp;

	float spawnTime;
	float currentSpawnTimer;

	float PowerUpTimer;
	float currentPowerUpTimer;


	std::vector<Enemy*> spawnedEnemies;
	std::vector<PowerUp*> createdPowerUps;

	void doSpawnLogic();
	void doCollisionLogic();
	void spawn();
	void despawnEnemy(Enemy* enemy);
	void spawnPowerUp();
	void deleteUnseenObjects();
	void deleteClaimedPowerUps(PowerUp* powerUp);
	void createPowerUps();

	int powerUpCount;
	int points;
};

