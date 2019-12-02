#include "SpawnManager.h"
#include "Type.h"
#include "Player.h"
#include "GameObject.h"
#include <iostream>

#include <cstdlib>
#include <ctime>


#pragma region Constructor & Destructor

SpawnManager::SpawnManager()
{
	counter = 0;
	counter1 = 0;
	counter2 = 0;
}

SpawnManager::~SpawnManager()
{}

#pragma endregion


#pragma region Spawn functions

//Function that spawns enemies until the player dies
void SpawnManager::SpawnEnemies(GameWorld* game, float deltaTime, float timeBetweenSpawns)
{
	//adds the time between frames to the timer, so the spawning will be controlled in seconds
	spawnTimer += deltaTime;

	//IF the timer´s time is greater then the time set for next spawn then a new enemy is spawned
	if (spawnTimer > timeBetweenSpawns)
	{
		//generates a random value between 0-2 based upon the time since the application started,
		//which gives a true random value!
		srand(time(0));
		int val = rand() % 3;

		//generates a random value between 650 - 1200 i x position.
		//which gives the spawned enemy a new random position on the x-axis
		float posX = (rand() % (1200 - 650)) + 650;

		//spawns a enemy with randomly choosen movement- and shooting type, base on the random value int val variable have
		game->SpawnGameObject(new Enemy(posX, -100.f,
			val == 0 ? Enemy::MovementTypes::Circle : val == 1 ? Enemy::MovementTypes::Horizontal : Enemy::MovementTypes::Vertical,
			val == 0 ? Enemy::ShootTypes::DoubleShot : val == 1 ? Enemy::ShootTypes::SingleShot : Enemy::ShootTypes::SpreadShot,
			"Res/Enemy Dragon.png"));

		//resets the timer, to check for next spawn
		spawnTimer = 0;
	}
}


//old function that spawns three game objects x amount of times, 
//initialized by delta time and time between spawns
void SpawnManager::SpawnEnemies(GameWorld* game,
	GameObject* gameObject, int numberOfGO,
	GameObject* gameObject1, int numberOfGO1,
	GameObject* gameObject2, int numberOfGO2,
	float deltaTime, float timeBetweenSpawns)
{
	//sets the timer to seconds, by using delta time which returns the time between frames 
	spawnTimer += deltaTime;

	//IF the timer is greater then the time for next spawn, then new game objects are spawned.
	if (spawnTimer > timeBetweenSpawns)
	{
		//and if the specific counter is less.. 
		//..then specified number of game objects that should be spawned.
		if (counter < numberOfGO)
		{
			//spawns a specified game object
			game->SpawnGameObject(gameObject);
			//one is added to the counter
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
		//resets the timer, to check for next spawn
		spawnTimer = 0;
	}
}

#pragma endregion


