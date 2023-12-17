#pragma once
#include <SDL2/SDL.h>


class Timer
{
public:
	Timer();

	void reset();
	void update();

	static float deltaTime;


private:
	Uint32 startTicks;
	Uint32 elapsedTicks;
};

