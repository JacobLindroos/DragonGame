#pragma once

#include "Engine.h"
#include "GameObject.h"
#include "Time.h"

#define BACKGROUND_H 3200
#define BACKGROUND_W 800
#define SCREEN_W 1920
#define SCREEN_H 1080
#define SCROLLING_BKG_SPEED 80.f

class Background : public GameObject
{
public:
	Background(float posX, float posY, int width, int height, const char* path);

	SDL_Rect srcRect;
	SDL_FRect destRect;

	const char* _path;
	float _width;
	float _height;

	void Update(float deltaTime) override;
	void Render() override;
};