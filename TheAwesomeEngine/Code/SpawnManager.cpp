#include "SpawnManager.h"
#include "Type.h"
#include "Player.h"
#include "GameObject.h"
#include <iostream>

#include <cstdlib>
#include <ctime>



SpawnManager::SpawnManager()
{

}

SpawnManager::~SpawnManager()
{
}

void SpawnManager::SpawnEnemies(GameWorld* game, float deltaTime, float timeBetweenSpawns)
{
	spawnTimer += deltaTime;

	if (spawnTimer > timeBetweenSpawns)
	{
		//generates a random value between 0-2 based upon the time since the application started,
		//which gives a true random value!
		srand(time(0));
		int val = rand() % 3;

		//generates a random value between 650 - 1200 i x position.
		float posX = (rand() % (1200 - 650)) + 650;

		//spawns a enemy with randomly choosen movement- and shooting type, base on the random value int val variable have
		game->SpawnGameObject(new Enemy(posX, -100.f, 
								  val == 0 ? Enemy::MovementTypes::Circle : val == 1 ? Enemy::MovementTypes::Horizontal : Enemy::MovementTypes::Vertical, 
								  val == 0 ? Enemy::ShootTypes::DoubleShot : val == 1 ? Enemy::ShootTypes::SingleShot : Enemy::ShootTypes::SpreadShot, 
								  "Res/Ma_Man_Enemy.png"));
		spawnTimer = 0;
	}
}


void SpawnManager::SpawnEnemies(GameWorld* game,
	GameObject* gameObject, int numberOfGO,
	GameObject* gameObject1, int numberOfGO1,
	GameObject* gameObject2, int numberOfGO2,
	float deltaTime, float timeBetweenSpawns)
{
	timer += deltaTime;

	spawnTimer += deltaTime;

	if (spawnTimer > timeBetweenSpawns)
	{
		if (counter < numberOfGO)
		{
			game->SpawnGameObject(gameObject);
			counter++;
		}
		if (counter1 < numberOfGO1)
		{
			game->SpawnGameObject(gameObject1);
			counter1++;
		}
		if (counter2 < numberOfGO2)
		{
			game->SpawnGameObject(gameObject2);
			counter2++;
		}
		spawnTimer = 0;
	}
}

