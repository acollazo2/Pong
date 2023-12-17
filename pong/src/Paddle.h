#pragma once

#include <SDL2/SDL.h>
#include <iostream>


class Paddle
{
public:
	Paddle(int startingX);

	int& x();
	int& y();
	void moveUp();
	void moveDown();
	SDL_Rect* getRect();
	void resetPos();

public:
	static const int paddleHeight = 100;
	static const int paddleWidth = 7;

private:
	SDL_Rect paddleRect; // this contains the current x and y

	int startingX;
	int startingY;

	int speed = 300;
};

