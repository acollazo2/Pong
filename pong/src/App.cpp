#include <SDL2/SDL.h>
#include "App.h"
#include "Timer.h"
#include <cstdio>


SDL_Window* App::window = NULL;
SDL_Renderer* App::renderer = NULL;

App::~App()
{
	if (window != NULL)
	{
		SDL_DestroyWindow(window);
		window = NULL;
	}
	if (renderer != NULL)
	{
		SDL_DestroyRenderer(renderer);
		renderer = NULL;
	}
	SDL_Quit();
}

bool App::init()
{
	if (SDL_Init(SDL_INIT_VIDEO) < 0)
	{
		printf("SDL Initialization failed: %s\n", SDL_GetError());
		return false;
	}

	window = SDL_CreateWindow("Pong", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, WINDOW_WIDTH, WINDOW_HEIGHT, SDL_WINDOW_SHOWN);
	if (window == NULL)
	{
		printf("SDL window creation failed: %s\n", SDL_GetError());
		return false;
	}

	renderer = SDL_CreateRenderer(window, -1, 0);
	if (renderer == NULL)
	{
		printf("SDL renderer creation failed: %s\n", SDL_GetError());
		return false;
	}

	return true;
}

void App::run()
{
	bool running = true;

	while (running)
	{
		timer.update();
		
		if (timer.deltaTime >= 1.0f / FRAME_RATE) //keep calling timer.update() until deltatime increases to the required deltatime of our framerate
		{

			if (SDL_PollEvent(&event)) //if theres an event this frame then handle that event
			{
				if (event.type == SDL_QUIT)
				{
					running = false;
					break;
				}
				game.handleInputs();
			}

			game.update();
			game.render();
			timer.reset();
		}


	}
}

SDL_Window* App::getWindow()
{
	return window;
}

SDL_Renderer* App::getRenderer()
{
	return renderer;
}
