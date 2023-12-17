#pragma once

#include <SDL2/SDL.h>
#include "Pong.h"
#include "Timer.h"

class App
{
public:
	~App();
	bool init();
	void run();
	static SDL_Window* getWindow();
	static SDL_Renderer* getRenderer();

public:
	static const int WINDOW_WIDTH = 960;
	static const int WINDOW_HEIGHT = 540;

	Uint8 FRAME_RATE = 60;

private:
	static SDL_Window* window;
	static SDL_Renderer* renderer;
	SDL_Event event;

	Timer timer;

	Pong game;
};
