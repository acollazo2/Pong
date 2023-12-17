#include "Paddle.h"
#include "App.h"
#include "Timer.h"


Paddle::Paddle(int startingX) : startingX(startingX), startingY(App::WINDOW_HEIGHT/2 - paddleHeight/2)
{
	resetPos();
	paddleRect.h = paddleHeight;
	paddleRect.w = paddleWidth;
}

int& Paddle::x()
{
	return paddleRect.x;
}

int& Paddle::y()
{
	return paddleRect.y;
}

void Paddle::moveUp()
{
	y() -= speed * Timer::deltaTime;

	if (y() < 0)
		y() = 0;
}

void Paddle::moveDown()
{
	y() += speed * Timer::deltaTime;

	if (y() > App::WINDOW_HEIGHT-paddleHeight)
		y() = App::WINDOW_HEIGHT-paddleHeight;
}

SDL_Rect* Paddle::getRect()
{
	return &paddleRect;
}

void Paddle::resetPos()
{
	x() = startingX;
	y() = startingY;
}
