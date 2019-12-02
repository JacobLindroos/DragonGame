#pragma once

#include "UI/UIManager.h"
#include "Time.h"

//defning the max amount of game object in the game
#define MAX_GAME_OBJECTS 250

//forward the game object class
class GameObject;

//class for handling the game world, i.e. updating and rendering game objects
class GameWorld
{
public:
	//con- & destructor
	GameWorld();
	~GameWorld();

	//array of game objects called Objects, wit max_game_objects as length
	GameObject* Objects[MAX_GAME_OBJECTS];
	//initialize the UI manager
	UIManager uiManager;

	//updating the game objects
	void Update(float deltaTime);
	//rendering the game objects
	void Render();
	//getting the UI manager
	UIManager* GetUIManager() { return &uiManager; }
	//spawning the game objects
	void SpawnGameObject(GameObject* go);
	//destroying the game objects
	void DestroyGameObjetc(GameObject* go);

};

