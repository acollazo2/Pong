#include "Ball.h"
#include "App.h"
#include "Timer.h"
#include "Paddle.h"
#include <random>
#include <cmath>
#include <iostream>

Ball::Ball()
{
	ballRect.w = ballRect.h = ballSize;
	reset();
}

void Ball::reset()
{
	x() = App::WINDOW_WIDTH/2;
	y() = App::WINDOW_HEIGHT/2;
	launch();
}

int& Ball::x()
{
	return ballRect.x;
}

int& Ball::y()
{
	return ballRect.y;
}

void Ball::move()
{
	int dx = std::round(velocityX*Timer::deltaTime);
	int dy = std::round(velocityY*Timer::deltaTime);

	if (dx == 0)
		dx = 1;

	x() += dx;
	y() += dy;
}

void Ball::bounceWall()
{
	velocityY *= -1;
}

void Ball::bouncePaddle(Paddle* paddle)
{
	double ballCenterPosY = y() + ballSize/2;
	double paddleCenterPosY = paddle->y() + paddle->paddleHeight/2;

	double ratioDistanceFromBallToPaddle = (ballCenterPosY-paddleCenterPosY) / (paddle->paddleHeight/2);

	bool hitLeftPaddle = velocityX < 0;
	if (hitLeftPaddle)
	{
		angle = 45 * ratioDistanceFromBallToPaddle; //set angle from either -45 to 45 degrees
	}
	else
	{
		angle = 180 + (-45 * ratioDistanceFromBallToPaddle); // set angle from either 135 to 225 degrees
	}
	
	velocityX = speed*std::cos(angle * M_PI/180.0);
	velocityY = speed*std::sin(angle * M_PI/180.0);
}

SDL_Rect* Ball::getRect()
{
	return &ballRect;
}

void Ball::launch()
{
	std::random_device rd;
	std::mt19937 gen(rd());
	std::uniform_int_distribution<int> ang(0, 360);
	angle = ang(gen);

	velocityX = speed*std::cos(angle * M_PI/180.0);
	velocityY = speed*std::sin(angle * M_PI/180.0);
}