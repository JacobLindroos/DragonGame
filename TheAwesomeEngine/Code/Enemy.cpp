#include "Enemy.h"
#include "Engine.h"
#include "Bullet.h"

Enemy::Enemy(float posX, float posY, MovementTypes mt, ShootTypes st, const char* path) : GameObject(posX, posY), movementSpeed(movementSpeed), mt(mt), st(st), _path(path)
{
	entityBoxCollider.x = posX;
	entityBoxCollider.y = posY;
	entityBoxCollider.width = 32;
	entityBoxCollider.height = 32;

	_directionX = 1.0f;
	_directionY = 1.0f;
	uim = GetUIManager();
}

void Enemy::Update(float deltaTime)
{


	entityBoxCollider.x = _posX;
	entityBoxCollider.y = _posY;
	entityBoxCollider.width = 32;
	entityBoxCollider.height = 32;

	if (mt == MovementTypes::Circle)
	{
		CircleMove();
		if (centerPosition.y > 25.f && centerPosition.y < 800.f)
		{
			CheckAmmuntion();
		}
	}
	if (mt == MovementTypes::Horizontal)
	{
		HorizontalMove();
		if (_posX > 560.f && _posX < 1300.0f)
		{
			CheckAmmuntion();
		}
	}
	if (mt == MovementTypes::Vertical)
	{
		VerticalMove();
		if (_posY > 25.f && _posY < 950.f)
		{
			CheckAmmuntion();
		}
	}


	timer += deltaTime;
}


//Renders the enemy sprite 
void Enemy::Render()
{
	if (_path)
	{
		EngineRenderTexture(_posX, _posY, 64, 64, _path);
	}
	else
	{
		EngineRenderSquare(_posX, _posY, 32, 32);
	}
}


void Enemy::CircleMove()
{
	angle += 0.1f;

	float x = centerPosition.x + cos(angle) * radius;
	float y = centerPosition.y + sin(angle) * radius;

	_posX = x;
	_posY = y;

	centerPosition.y += .8f;

	if (centerPosition.y > 1100.f)
	{
		uim->UpdateScore(-1);
		_gameWorld->DestroyGameObjetc(this);
	}
}


void Enemy::HorizontalMove()
{
	_posX += 3.f;

	if (_posX > 1300.f)
	{
		_posX = 560.f;
		_posY += 100.f;

		if (_posY > 1100.f)
		{
			uim->UpdateScore(-1);
			_gameWorld->DestroyGameObjetc(this);
		}
	}
}


void Enemy::VerticalMove()
{
	_posY += 3.f;

	if (_posY > 1100.f)
	{
		uim->UpdateScore(-1);
		_gameWorld->DestroyGameObjetc(this);
	}
}


void Enemy::CheckAmmuntion()
{
	if (timer > 1)
	{
		if (st == ShootTypes::SingleShot)
		{
			_gameWorld->SpawnGameObject(new Bullet(_posX + 16, _posY + 64 * _directionY, 0, _directionY,"Res/FireBall.png" , "Enemy"));
		}
		if (st == ShootTypes::DoubleShot)
		{
			_gameWorld->SpawnGameObject(new Bullet(_posX + 46, _posY + 64 * _directionY, 0, _directionY, "Res/FireBall.png", "Enemy"));
			_gameWorld->SpawnGameObject(new Bullet(_posX -14, _posY + 64 * _directionY, 0, _directionY, "Res/FireBall.png", "Enemy"));
		}
		if (st == ShootTypes::SpreadShot)
		{
			_gameWorld->SpawnGameObject(new Bullet(_posX + 26, _posY + 64 * _directionY, -1, _directionY, "Res/FireBall.png", "Enemy"));
			_gameWorld->SpawnGameObject(new Bullet(_posX + 16, _posY + 64 * _directionY, 0, _directionY, "Res/FireBall.png", "Enemy"));
			_gameWorld->SpawnGameObject(new Bullet(_posX - 6, _posY + 64 * _directionY, 1, _directionY, "Res/FireBall.png", "Enemy"));
		}
		timer = 0;
	}
}
