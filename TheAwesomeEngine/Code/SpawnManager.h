#pragma once

#include "GameObject.h"
#include "GameWorld.h"
#include "Enemy.h"
#include "Time.h"

#include <iostream>



class SpawnManager
{
public:
	SpawnManager();
	~SpawnManager();

	void SpawnEnemies(GameWorld* game,float deltaTime, float timeBetweenSpawns);

	void SpawnEnemies(GameWorld* game, GameObject* gameObject, int thisManyGO, GameObject* gameObject1, int thisManyGO1, GameObject* gameObject2, int thisManyGO2, float deltaTime, float timeBetweenSpawns);

private:
	int counter = 5;
	int counter1 = 0;
	int counter2 = 0;
	float spawnTimer = 0;
	float timer = 0;

};