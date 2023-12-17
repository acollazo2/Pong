#pragma once
#include <SDL2/SDL.h>
#include "Paddle.h"

class Ball
{
public:
	Ball();

	void reset();
	int& x();
	int& y();
	void move();
	void bounceWall();
	void bouncePaddle(Paddle* paddle);
	SDL_Rect* getRect();

public:
	const int ballSize = 7;

	double velocityX;
	double velocityY;

private:
	void launch();

	void test();

private:
	SDL_Rect ballRect;

	const int speed = 500;
	double angle;
};

