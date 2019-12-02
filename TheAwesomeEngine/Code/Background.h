#pragma once

#include "Engine.h"
#include "GameObject.h"
#include "Time.h"

//defining background and screen size, also setting the scrolling speed of the background
#define BACKGROUND_H 3200
#define BACKGROUND_W 800
#define SCREEN_W 1920
#define SCREEN_H 1080
#define SCROLLING_BKG_SPEED 95.f

//class for creating the background, deriving from the game object class
class Background : public GameObject
{
public:
	//constructor of backgorund, which sets it´s size, width, height and takes a path to it´s source file
	Background(float posX, float posY, int width, int height, const char* path);

	//creating two rects, used to create a scrolling background
	SDL_Rect srcRect;
	SDL_FRect destRect;

	//path file variable
	const char* _path;
	//width and height variable for background
	float _width;
	float _height;

	//function for updating the background, overrides the derived update function from gameObject
	void Update(float deltaTime) override;
	//function for rendering the background
	void Render() override;
};