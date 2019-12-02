#pragma once

#include "GameObject.h"
#include "GameWorld.h"
#include "Enemy.h"
#include "Time.h"

#include <iostream>

//class taking care of spawning enemies into the game
class SpawnManager
{
public:
	//constructor and destructor for the class
	SpawnManager();
	~SpawnManager();

	//function for spawning enemies into the game and one overload function
	void SpawnEnemies(GameWorld* game, float deltaTime, float timeBetweenSpawns);
	void SpawnEnemies(GameWorld* game, GameObject* gameObject, int thisManyGO, GameObject* gameObject1, int thisManyGO1, GameObject* gameObject2, int thisManyGO2, float deltaTime, float timeBetweenSpawns);

private:
	//counters keeping trak of how many enemies that has been spawned, used in the overload function
	int counter;
	int counter1;
	int counter2;

	//timer used for keeping track of when a enemy is to be spawned
	float spawnTimer = 0;

};