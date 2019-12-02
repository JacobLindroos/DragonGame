#pragma once

#include <SDL.h>
#include "Time.h"
#include "Background.h"
#include "Player.h"
#include "Enemy.h"
#include "SpawnManager.h"
#include "Engine.h"
#include "GameManager.h"
#include "UI/UIManager.h"


//class that manage the game
class GameManager
{
public:
	//constructor and destructor
	GameManager();
	~GameManager();

	//funtion that holds starting functions
	void Start();
	//function that holds all update functions
	void Update();
	//function that holds quit functions
	void Quit();

private:
	//sets the framerate, which is used to calculate the time between frames
	const float targetFramerate = 80;
	//calculates the frame delay, which is used to achieve target framerate
	const float frameDelay = 1000 / targetFramerate;

	//initialize time, spawnmanager, gameworld
	GameWorld game;
	SpawnManager spawn;
	Time time;

	//creates a pointer to enemy, player and background
	Enemy* enemy;
	Player* player;
	Background* background;
};