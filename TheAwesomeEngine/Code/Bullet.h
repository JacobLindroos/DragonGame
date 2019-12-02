#pragma once
#include "GameObject.h"
#include "UI/UIManager.h"

#define BULLET_SPEED 40.F
#define BULLET_HEIGHT 20
#define BULLET_WIDTH 20

class Bullet :public GameObject {
public:
	UIManager* _UImanager;

	Bullet(float x, float y, float dirX, float dirY, const char* path, const char* shooter): GameObject(x, y), _dirX(dirX), _dirY(dirY), _path(path), _shooter(shooter)
	{
		_UImanager = GetUIManager();
	}

	const char* _path;

	const char* _shooter;

	void Update(float deltaTime) override;
	void Render() override;

private:
	float _dirX;
	float _dirY;
};