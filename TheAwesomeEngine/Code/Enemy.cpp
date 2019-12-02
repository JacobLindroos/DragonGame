#include "Enemy.h"
#include "Engine.h"
#include "Bullet.h"
#include "UI/UIManager.h"


#pragma region Constructor

//Constructor for Enemy, which initialize the enemy큦 position, size, shooting and movement
Enemy::Enemy(float posX, float posY, MovementTypes mt, ShootTypes st, const char* path) : GameObject(posX, posY), mt(mt), st(st), _path(path)
{
	//initialize the enemy큦 collidingbox
	entityBoxCollider.x = posX;
	entityBoxCollider.y = posY;
	entityBoxCollider.width = ENEMY_W;
	entityBoxCollider.height = ENEMY_H;

	//initialize the direction of the enemy큦 movement and shooting
	_directionX = 1.0f;
	_directionY = 1.0f;

	//gets the UI manager
	uim = GetUIManager();
}

#pragma endregion


#pragma region Update

//update function of enemy
//updating the collisionbox, it큦 movement, shooting and timer
void Enemy::Update(float deltaTime)
{
	entityBoxCollider.x = _posX;
	entityBoxCollider.y = _posY;
	entityBoxCollider.width = ENEMY_W;
	entityBoxCollider.height = ENEMY_H;

	if (mt == MovementTypes::Circle)
	{
		CircleMove();
		//if the enemy큦 movement is between 25 and 800 on y aixs, the enemy is allowed to shoot
		if (centerPosition.y > 25.f && centerPosition.y < 800.f)
		{
			CheckAmmunition();
		}
	}
	if (mt == MovementTypes::Horizontal)
	{
		HorizontalMove();
		//if the enemy큦 movement is between 560 and 1300 on x axis, the enemy is allowed to shoot
		if (_posX > 560.f && _posX < 1300.0f)
		{
			CheckAmmunition();
		}
	}
	if (mt == MovementTypes::Vertical)
	{
		VerticalMove();
		//if the enemy큦 movement is between 25 and 800 on y aixs, the enemy is allowed to shoot
		if (_posY > 25.f && _posY < 800.f)
		{
			CheckAmmunition();
		}
	}
	timer += deltaTime;
}

#pragma endregion


#pragma region Render

//Renders a enemy in the game
void Enemy::Render()
{
	EngineRenderTexture(_posX, _posY, ENEMY_W, ENEMY_H, _path);
}

#pragma endregion


#pragma region Movement

//gives the enemy a circle movement
void Enemy::CircleMove()
{
	//increasing the angle by 0.1 every update
	angle += 0.1f;
	//calculates the x- and y-position of the enemy so it moves in a circle
	float x = centerPosition.x + cos(angle) * radius;
	float y = centerPosition.y + sin(angle) * radius;
	//sets the enemy큦 position to calculated x and y from the centerpositions x- and y-value
	_posX = x;
	_posY = y;
	//moves the eneym forward in a circle movement, by moving the circle큦 centerpostion forward
	centerPosition.y += movementSpeed * 0.27f;
	//IF the enemy큦 position is greater then 1100 the player loses score
	//because it got past the player, then the enemy is destroyed
	if (centerPosition.y > ENEMY_WIN_POS)
	{
		uim->UpdateScore(-1);
		_gameWorld->DestroyGameObjetc(this);
	}
}


//gives the enemy a horizontal movement
void Enemy::HorizontalMove()
{
	//moves the enemy forward on the x-axis
	_posX += movementSpeed;
	//IF the enemy큦 position is greater then 1300.f the enemy is moved
	//down 100 on the y-axis and start큦 over on the x-axis
	if (_posX > BCK_RIGHT_EDGE)
	{
		_posX = BCK_LEFT_EDGE;
		_posY += 100.f;
		//IF the enemy큦 position is greater then 1100 the player loses score
		//because it got past the player, then the enemy is destroyed
		if (_posY > ENEMY_WIN_POS)
		{
			uim->UpdateScore(-1);
			_gameWorld->DestroyGameObjetc(this);
		}
	}
}


//gives the enemy a vertical movement
void Enemy::VerticalMove()
{
	//moves the enemy downwards on the y-axis
	_posY += movementSpeed;
	//IF the enemy큦 position is greater then 1100 the player loses score
	//because it got past the player, then the enemy is destroyed
	if (_posY > ENEMY_WIN_POS)
	{
		uim->UpdateScore(-1);
		_gameWorld->DestroyGameObjetc(this);
	}
}

#pragma endregion


#pragma region Shooting

//checking for which ammunition the enemy is using
void Enemy::CheckAmmunition()
{
	//timer for how often the enemy is allowed to shoot
	if (timer > shootRate)
	{
		//IF the enemy is shooting singleShot큦 then spawn single shot
		if (st == ShootTypes::SingleShot)
		{
			_gameWorld->SpawnGameObject(new Bullet(_posX + 16, _posY + 64 * _directionY, 0, _directionY, "Res/Enemybullet.png", "Enemy"));
		}
		//IF the enemy is shooting doubleshot큦 then spawn double shot
		if (st == ShootTypes::DoubleShot)
		{
			_gameWorld->SpawnGameObject(new Bullet(_posX + 46, _posY + 64 * _directionY, 0, _directionY, "Res/Enemybullet.png", "Enemy"));
			_gameWorld->SpawnGameObject(new Bullet(_posX - 14, _posY + 64 * _directionY, 0, _directionY, "Res/Enemybullet.png", "Enemy"));
		}
		//IF the enemy is shooting spreadshot큦 then spawn spread shot
		if (st == ShootTypes::SpreadShot)
		{
			_gameWorld->SpawnGameObject(new Bullet(_posX + 26, _posY + 64 * _directionY, -1, _directionY, "Res/Enemybullet.png", "Enemy"));
			_gameWorld->SpawnGameObject(new Bullet(_posX + 16, _posY + 64 * _directionY, 0, _directionY, "Res/Enemybullet.png", "Enemy"));
			_gameWorld->SpawnGameObject(new Bullet(_posX - 6, _posY + 64 * _directionY, 1, _directionY, "Res/Enemybullet.png", "Enemy"));
		}
		//resets the timer for how often the player is allowed to shoot
		timer = 0;
	}
}

#pragma endregion
