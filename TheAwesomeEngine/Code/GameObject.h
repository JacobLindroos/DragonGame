#pragma once
#include "GameWorld.h"
#include "Borders.h"
#include <SDL.h>

//class for creating different game objects
class GameObject
{
public:
	//Con- & destructor
	GameObject() {}
	GameObject(float x, float y);

	//Update and render function for game object´s
	virtual void Update(float deltaTime) = 0;
	virtual void Render();

	//gives the specific game object a x- and y-position
	int _posX, _posY;

	//initialize a collisionbox and the game world
	Bounds entityBoxCollider;
	GameWorld* _gameWorld;
};
