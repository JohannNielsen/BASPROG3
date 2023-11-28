#pragma once
#include "Scene.h"
#include "GameObject.h"
#include "Player.h"
#include "Enemy.h"
#include <vector>
#include "text.h"
#include "PowerUp.h"
#include "Boss.h"
#include "Background.h"

class GameScene : public Scene
{
public:

	GameScene();
	~GameScene();

	void start();
	void draw();
	void update();

private:
	Background* background;

	Player* player;
	Enemy* enemy;
	Boss* boss;

	PowerUp* powerUp;
	Bullet* tempBullet2;

	Mix_Chunk* sound1;
	Mix_Chunk* sound2;

	float spawnTime;
	float currentSpawnTimer;
	float PowerUpTimer;
	float currentPowerUpTimer;
	float bossSpawnTimer;
	float bossTimerReset;
	float textTimer;
	float timer;

	std::vector<Enemy*> spawnedEnemies;
	std::vector<PowerUp*> createdPowerUps;
	std::vector<Bullet*> tempBullet;

	void doSpawnLogic();
	void doCollisionLogic();
	void spawn();
	void despawnEnemy(Enemy* enemy);
	void spawnPowerUp();
	void deleteUnseenObjects();
	void deleteClaimedPowerUps(PowerUp* powerUp);
	void createPowerUps();
	void spawnBoss();
	void createBackGround();


	int powerUpCount;
	int points;
	int level;

	int wave;
	int tempWave;
	int numWaves;

	int bossStat;
	int bossHp;
	int bossHpAdd;
};