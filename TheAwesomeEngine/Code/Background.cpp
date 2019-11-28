#include "Background.h"
#include <iostream>

Background::Background(float posX, float posY, int width, int height, const char* path) : GameObject(posX, posY), _width(width), _height(height), _path(path)
{
	srcRect.x = 0;
	srcRect.y = 0;
	srcRect.h = BACKGROUND_H;
	srcRect.w = BACKGROUND_W;

	destRect.x = SCREEN_W / 2 - (BACKGROUND_W / 2);
	destRect.y = -BACKGROUND_H / 2;
	destRect.h = BACKGROUND_H;
	destRect.w = BACKGROUND_W;
}

void Background::Update(float deltaTime)
{
	destRect.y -= SCROLLING_BKG_SPEED * deltaTime;

	if (destRect.y <= -BACKGROUND_H / 2)
	{
		destRect.y = 0;
	}
}

void Background::Render()
{
	EngineRenderBackground(&srcRect, &destRect, _path);
}
