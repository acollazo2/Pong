#include <SDL2/SDL.h>
#include "App.h"
#include <cstdio>
#undef main

int main()
{
	App app;

	if (!app.init())
	{
		printf("Error initializing program.\n");
		return 420;
	}

	app.run();
}