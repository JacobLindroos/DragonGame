#pragma once
#include "GameObject.h"
#include "Vector.h"
#include "Engine.h"
#include "Time.h"

//defines a radius w. a float value of 100 and the enemy큦 width and height
#define RADIUS 100.f
#define ENEMY_W 64
#define ENEMY_H 64
#define ENEMY_WIN_POS 1100.f
#define BCK_LEFT_EDGE 560.f
#define BCK_RIGHT_EDGE 1300.f

//class that creates a enemy, deriving from GameObject class
class Enemy : public GameObject
{
public:
	//enum class called movement type, which holds a list of three different movements for the enemy
	enum class MovementTypes
	{
		Circle, Horizontal, Vertical,
	};

	//enum class called shoot type, which holds a list of three different shooting types for the enemy
	enum class ShootTypes
	{
		SingleShot, DoubleShot, SpreadShot,
	};

	//constructor for Enemy
	Enemy(float posX, float posY, MovementTypes mt, ShootTypes st, const char* _path);

	//initialize a shootingtype
	ShootTypes st;
	//initialize a movementtype
	MovementTypes mt;
	//creating a pointer to the UI manager
	UIManager* uim;
	//creates vector called centerPosition, used for calculating the centerposition of a circle
	Vector centerPosition = Vector(_posX, _posY);

	//setting the angle to use for calculating the circle movement
	float angle = 0.f;
	//radius for calculating the circle movement
	float radius = RADIUS;
	//used to set the direction for the enemy큦 movement and shooting
	float _directionX;
	float _directionY;
	//timer for enemy shooting
	float timer = 0;
	//holds path to enemy sprite file
	const char* _path;
	//movement speed of the enemy
	float movementSpeed = 3.f;
	//shooting rate
	float shootRate = 1.f;

	//function that updates the enemy큦 movement, shooting and collidingbox
	void Update(float deltaTime) override;
	//function that renders the enemy큦 sprite file
	void Render() override;
	//moving the enemy forward in a circler pattern
	void CircleMove();
	//moving the enemy forward on the x axis
	void HorizontalMove();
	//moving the enemy forward on the y axis
	void VerticalMove();
	//firing a bullet type 
	void CheckAmmunition();
};