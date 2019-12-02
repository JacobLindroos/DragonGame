#include "Bullet.h"
#include "Engine.h"
#include "Type.h"
#include "Enemy.h"
#include "Player.h"
#include "Borders.h"
#include "Background.h"

#include <SDL.h>
#include <iostream>

void Bullet::Update(float deltaTime)
{
	Bounds screenBounds = Bounds(544, 0, 1360, SCREEN_H); //Have to set specifikt numbers so it matches the midle screen and so the bullets doesn't go into the black screen

	_posX += BULLET_SPEED * _dirX;
	_posY += BULLET_SPEED * _dirY;

#pragma region CollisionBox
	//Collisionbox for the bullet
	entityBoxCollider.x = _posX;
	entityBoxCollider.y = _posY;
	entityBoxCollider.width = BULLET_WIDTH;
	entityBoxCollider.height = BULLET_HEIGHT;
#pragma endregion

#pragma region Hit detection
	//Checks if the bullet hit an entity and who
	for (int i = 0; i < MAX_GAME_OBJECTS; i++)
	{
		GameObject* goPtr = _gameWorld->Objects[i]; //Comapres the goptr to the list of objects we have
		if (goPtr == nullptr || goPtr == this)
		{
			continue;
		}

		if (IsA<Enemy>(goPtr) && _shooter != "Enemy") //If the object is an enemy and the bullet did't come from enemy
		{
			if (entityBoxCollider.CollidesWith(goPtr->entityBoxCollider)) {
				_gameWorld->DestroyGameObjetc(goPtr); //Destroy the enity it collided with
				_UImanager->UpdateScore(1); //Update the score witha positive number
				_gameWorld->DestroyGameObjetc(this); //Last destroy the bullet

				return;
			}
		}


		if (IsA<Player>(goPtr) && _shooter != "Player") //If the object is an enemy and the bullet did't come from the player
		{
			if (entityBoxCollider.CollidesWith(goPtr->entityBoxCollider))
			{
				_UImanager->UpdateLife(); //Updates the number of lives player has left
				_gameWorld->DestroyGameObjetc(this); //Destroys the bullet
				return;
			}
		}
	}
#pragma endregion

#pragma region Bounds checking
	//Basically an AABB collision check between the bullet and the playerscreen
	//And if it hits with the walls then destroy the bullet
	if (_posX <= screenBounds.x)
	{
		_gameWorld->DestroyGameObjetc(this);
		return;
	}
	else if (_posX + 32 >= screenBounds.width)
	{
		_gameWorld->DestroyGameObjetc(this);
		return;
	}

	if (_posY <= screenBounds.y)
	{
		_gameWorld->DestroyGameObjetc(this);
		return;
	}
	else if (_posY + 64 >= screenBounds.height)
	{
		_gameWorld->DestroyGameObjetc(this);
		return;
	}
#pragma endregion
}

void Bullet::Render()
{
	if (_path)
	{
		EngineRenderTexture(_posX, _posY, 30, 30, _path);
	}
	else
	{
		EngineRenderSquare(_posX, _posY, 20, 20);
	}
}
