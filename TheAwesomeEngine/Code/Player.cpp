#include "Player.h"
#include "Engine.h"
#include "Key.h"
#include "Bullet.h"
#include "MathHelper.h"
#include "UI/UIManager.h"
#include <math.h>
#include <iostream>
#include "Background.h"

Player::Player(float x, float y, ShootingTypes st, SpecialAttacks sa) : GameObject(x, y), _st(st), _sa(sa) {}

Player::Player(float x, float y, const char* path, ShootingTypes st, SpecialAttacks sa) : GameObject(x, y), _path(path), _st(st), _sa(sa) {}

void Player::Update(float deltaTime)
{
	Bounds screenBounds = Bounds(544, 0, 1343, SCREEN_H);

	//Timers
	circleTimer += EngineGetDeltaTime();
	normalShootingTimer += EngineGetDeltaTime();
	flameTimer += EngineGetDeltaTime();

	float _directionX = 0.0f;
	float _directionY = 0.0f;

	if (_directionX == 0.f && _directionY == 0.f)
	{
		_directionX++;
	}

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
		_posY -= 10.f;
		_directionY--;
	}
	if (EngineGetKey(Key::S))
	{
		_posY += 10.f;
		_directionY++;
	}
	if (EngineGetKey(Key::D))
	{
		_posX += 10.f;
		_directionX++;
	}
	if (EngineGetKey(Key::A))
	{
		_posX -= 10.f;
		_directionX--;
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
		_sa = Missiles;
	}


#pragma endregion

#pragma region Firing
	if (_st != Flamethrower && EngineGetKeyDown(Key::Space))
	{
		if (normalShootingTimer >= 0.5f)
		{
			if (_st == Normal)
			{
				_gameWorld->SpawnGameObject(new Bullet(_posX + 16, _posY + 32 * _directionY, 0, -1, "Res/FireBall_1.png", "Player"));
			}
			if (_st == Shotgun)
			{
				for (int i = 1; i <= (shotgunBulletCount); i++)
				{
					_gameWorld->SpawnGameObject(new Bullet(_posX, _posY, cos(i * shotgunAngle), sin(-i * shotgunAngle), "Res/FireBall_1.png", "Player"));
				}
			}
			normalShootingTimer = 0;
		}
	}
	else if (_st == Flamethrower && EngineGetKey(Key::Space)) //Firing the flamethrower
	{
		if (flameTimer > 0 && flameTimer < 2.f)
		{
			_gameWorld->SpawnGameObject(new Bullet(_posX + 16, _posY + 32 * _directionY, 0, -1, "Res/FireBall_1.png", "Player"));
		}
		if (flameTimer >= 8.f)
		{
			flameTimer = 0;
		}
	}

	if (_sa == CircleBomb && EngineGetKeyDown(Key::Space))
	{
		if (circleTimer >= 10.f)
		{
			for (int i = 1; i <= (bulletCount - 1) * 0.5; i++)
			{
				_gameWorld->SpawnGameObject(new Bullet(_posX, _posY, cos(i * angle), sin(i * angle), "Res/Bullet.png", "Player"));
				_gameWorld->SpawnGameObject(new Bullet(_posX, _posY, cos(-i * angle), sin(-i * angle), "Res/Bullet.png", "Player"));
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

