#include "Time.h"

void Time::StartFrame()
{
	startTime = SDL_GetPerformanceCounter();
}

void Time::EndFrame()
{
	endTime = SDL_GetPerformanceCounter();
	deltaTime = (endTime - startTime) / (float)SDL_GetPerformanceFrequency();
}


