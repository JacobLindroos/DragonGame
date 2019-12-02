#include "GameWorld.h"
#include "GameObject.h"
#include <iostream>
#include <algorithm>
#include <iterator>

#pragma region Con- & destructor

GameWorld::GameWorld()
{
	for (int i = 0; i < MAX_GAME_OBJECTS; i++)
	{
		Objects[i] = nullptr;
	}
}

GameWorld::~GameWorld()
{
	for (int i = 0; i < MAX_GAME_OBJECTS; i++)
	{
		if (Objects[i] != nullptr)
		{
			delete Objects[i];
			Objects[i] = nullptr;
		}
	}
}

#pragma endregion


//updates all game object´s update functions, if there is no game objects then continue
void GameWorld::Update(float deltaTime)
{
	for (int i = 0; i < MAX_GAME_OBJECTS; i++)
	{
		if (Objects[i] == nullptr)
			continue;

		Objects[i]->Update(deltaTime);

	}
	uiManager.Update();
}

//render all game objects, if there is no game objects then continue
void GameWorld::Render()
{
	for (int i = 0; i < MAX_GAME_OBJECTS; i++)
	{
		if (Objects[i] == nullptr)
			continue;

		Objects[i]->Render();
	}
	uiManager.Render();

}

//spawns game objects
void GameWorld::SpawnGameObject(GameObject* go)
{
	for (int i = 0; i < MAX_GAME_OBJECTS; i++)
	{
		if (Objects[i] == nullptr)
		{
			Objects[i] = go;
			break;
		}
	}
	go->_gameWorld = this;
}

//destroys game objects
void GameWorld::DestroyGameObjetc(GameObject* go)
{
	for (int i = 0; i < MAX_GAME_OBJECTS; i++)
	{
		if (Objects[i] == go) {
			Objects[i] = nullptr;
			delete go;
			break;
		}
	}
}
