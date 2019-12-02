#pragma once
#include "GameObject.h"
#include "Engine.h"
#include "Borders.h"
#include "Bullet.h"

class UIManager;

class Player :public GameObject {
public:
	//Diefferent shooting types the player can have
	enum ShootingTypes { 
		Normal,
		Flamethrower, 
		Shotgun
	};

	//Different special attacks the player can have, longer cooldown on these
	enum SpecialAttacks {
		None, 
		CircleBomb 
	};

	ShootingTypes _st;
	SpecialAttacks _sa;

	UIManager* UImanager;

	Player(float x, float y, ShootingTypes st, SpecialAttacks sa);
	Player(float x, float y, const char* path, ShootingTypes st, SpecialAttacks sa);

	const char* _path;

	void Update(float deltaTime) override;
	void Render() override;

	//Math for the circleBomb
	int bulletCount = 25;
	float angle = 2*M_PI / 25.f;
	float circleTimer = 0.f;

	//Math for the shotgun
	int shotgunBulletCount = 5;
	float shotgunAngle = 2*M_PI / 12;

	float normalShootingTimer = 0.f;

	float flameTimer = 0.f;
	float flamethrowerFuel = 0.f;

	float movementSpeed = 600.f;
private:
};