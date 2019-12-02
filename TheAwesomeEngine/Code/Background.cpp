#include "Background.h"
#include <iostream>

//constructor 
Background::Background(float posX, float posY, int width, int height, const char* path) : GameObject(posX, posY), _width(width), _height(height), _path(path)
{
	//initialize the size, width and height of the src rectangle
	//src rectangle is the orignal picture with it´s width and height
	srcRect.x = 0;
	srcRect.y = 0;
	srcRect.h = BACKGROUND_H;
	srcRect.w = BACKGROUND_W;

	//initialize the size, width and height of the dst rectangle
	//dst rectangle is used to create the illusion of a seemless scrolling background
	destRect.x = SCREEN_W / 2 - (BACKGROUND_W / 2);
	destRect.y = 0;
	destRect.h = BACKGROUND_H;
	destRect.w = BACKGROUND_W;
}


//function that updates the background
void Background::Update(float deltaTime)
{
	//giving dstRect a speed multiplied by delta time
	destRect.y -= SCROLLING_BKG_SPEED * deltaTime;
	//when the destRect value for y on the y-axis is less then the negative background height divided by two..
	//..then the destRect y value is reset to 0. Which creates the scrolling background effect
	if (destRect.y <= -BACKGROUND_H / 2)
	{
		destRect.y = 0;
	}
}


//functions that renders the background, by calling the engineRenderBackground function
void Background::Render()
{
	EngineRenderBackground(&srcRect, &destRect, _path);
}
