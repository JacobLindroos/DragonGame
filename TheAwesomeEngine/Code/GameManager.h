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


class GameManager
{
public:
	GameManager();
	~GameManager();

	void Start();
	void Update();
	void Quit();

private:
	const float targetFramerate = 80;
	const float frameDelay = 1000 / targetFramerate;
	float frametime = 0;

	SDL_Event keyEvent;

	GameWorld game;
	SpawnManager spawn;
	Time time;
	Enemy* enemy;
	Player* player;
	Background* background;
};