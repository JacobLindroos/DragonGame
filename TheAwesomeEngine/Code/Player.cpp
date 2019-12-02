#include "Player.h"
#include "Engine.h"
#include "Key.h"
#include "Bullet.h"
#include "UI/UIManager.h"
#include "Background.h"
#include <math.h>
#include <iostream>

Player::Player(float x, float y, ShootingTypes st, SpecialAttacks sa) : GameObject(x, y), _st(st), _sa(sa) {}

Player::Player(float x, float y, const char* path, ShootingTypes st, SpecialAttacks sa) : GameObject(x, y), _path(path), _st(st), _sa(sa) {}

void Player::Update(float deltaTime)
{
	Bounds screenBounds = Bounds(544, 0, 1343, SCREEN_H);

#pragma region Weapon timers
	circleTimer += EngineGetDeltaTime();
	normalShootingTimer += EngineGetDeltaTime();
	flameTimer += EngineGetDeltaTime();
#pragma endregion

#pragma region BoxCollider

	entityBoxCollider.x = _posX;
	entityBoxCollider.y = _posY;
	entityBoxCollider.width = 32;
	entityBoxCollider.height = 64;

#pragma endregion

#pragma region BoundsChecking

	if (_posX <= screenBounds.x)
	{
		_posX = screenBounds.x;
	}
	else if (_posX + 32 >= screenBounds.width)
	{
		_posX = screenBounds.width - 32;
	}

	if (_posY <= screenBounds.y)
	{
		_posY = screenBounds.y;
	}
	else if (_posY + 64 >= screenBounds.height)
	{
		_posY = screenBounds.height - 64;
	}
#pragma endregion

#pragma region Input

#pragma region Movement
	if (EngineGetKey(Key::W))
	{
		_posY -= EngineGetDeltaTime()*movementSpeed;
	}
	if (EngineGetKey(Key::S))
	{
		_posY += EngineGetDeltaTime() * movementSpeed;
	}
	if (EngineGetKey(Key::D))
	{
		_posX += EngineGetDeltaTime() * movementSpeed;
	}
	if (EngineGetKey(Key::A))
	{
		_posX -= EngineGetDeltaTime() * movementSpeed;
	}
#pragma endregion

#pragma region Weaponry

#pragma region ChangeWapons
	if (EngineGetKey(Key::NUM1))
	{
		_st = Normal;
	}

	if (EngineGetKey(Key::NUM2))
	{
		_st = Shotgun;
	}

	if (EngineGetKey(Key::NUM3))
	{
		_st = Flamethrower;
	}
	if (EngineGetKey(Key::NUM4))
	{
		_sa = CircleBomb;
	}
	if (EngineGetKey(Key::NUM5))
	{
		_sa = None;
	}


#pragma endregion

#pragma region Firing
	if (_st != Flamethrower && EngineGetKeyDown(Key::Space)) //If the current shooting type ins't flamethrower 
	{
		if (normalShootingTimer >= 0.5f) //Set a timer so you can't spam
		{
			if (_st == Normal) //If the shooting type is normal (aka. one bullet at a time)
			{
				_gameWorld->SpawnGameObject(new Bullet(_posX + 16, _posY + 32, 0, -1, "Res/Thingamajing.png", "Player"));
			}
			if (_st == Shotgun) //Or if the shooting type is shotgun (aka. shotgun duh)
			{
				for (int i = 1; i <= (shotgunBulletCount); i++)
				{
					_gameWorld->SpawnGameObject(new Bullet(_posX, _posY, cos(i * shotgunAngle), sin(-i * shotgunAngle), "Res/Thingamajing.png", "Player"));
				}
			}
			normalShootingTimer = 0; //Reset the timer
		}
	}
	else if (_st == Flamethrower && EngineGetKey(Key::Space)) //Firing the flamethrower
	{
		if (flamethrowerFuel > 0.f)
		{
			_gameWorld->SpawnGameObject(new Bullet(_posX + 16, _posY + 32, 0, -1, "Res/Thingamajing.png", "Player"));
			flamethrowerFuel -= EngineGetDeltaTime() * 10;
		}
	}
	if (flamethrowerFuel <= 0.f) //Refuels the fueltank 5 sec after the fuel runs out
	{
		flameTimer += EngineGetDeltaTime(); //Starts the counting for the timer

		if (flameTimer > 10.f)
		{
			flamethrowerFuel += 5.f;
			flameTimer = 0.f;
		}
	}

	if (_sa == CircleBomb && EngineGetKeyDown(Key::Space)) //Emits bullets in a circle around the player
	{
		if (circleTimer >= 10.f)
		{
			for (int i = 1; i <= (bulletCount - 1) * 0.5; i++) //Some high level math to calculate the angle of the shot depending on how many bullets you want to fire
			{
				_gameWorld->SpawnGameObject(new Bullet(_posX, _posY, cos(i * angle), sin(i * angle), "Res/Thingamajing.png", "Player"));
				_gameWorld->SpawnGameObject(new Bullet(_posX, _posY, cos(-i * angle), sin(-i * angle), "Res/Thingamajing.png", "Player"));
				circleTimer = 0;
			}
		}
	}
#pragma endregion
#pragma endregion

#pragma endregion 

	//Updates the position of the box collider
	entityBoxCollider.x = _posX;
	entityBoxCollider.y = _posY;
}

void Player::Render()
{
	if (_path) {
		EngineRenderTexture(_posX, _posY, 64, 64, _path);
	}
	else {
		EngineRenderSquare(_posX, _posY, 64, 64);
	}
}

