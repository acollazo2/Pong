#include "Timer.h"
#include <SDL2/SDL.h>

float Timer::deltaTime = 0.0f;

Timer::Timer()
{
	reset();
}

void Timer::reset()
{
	startTicks = SDL_GetTicks();
	elapsedTicks = 0;
	deltaTime = 0.0f;
}

void Timer::update()
{
	elapsedTicks = SDL_GetTicks() - startTicks;
	deltaTime = elapsedTicks * 0.001f;
}



