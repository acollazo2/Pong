#include "Pong.h"
#include "App.h"
#include "Paddle.h"
#include <iostream>


Pong::Pong() : leftPaddle(App::WINDOW_WIDTH * 0.05), rightPaddle(App::WINDOW_WIDTH * 0.95)
{
	reset();
}

//void Pong::handleInputs(SDL_Event* event)
//{
//	switch (event->type)
//	{
//	case SDL_KEYDOWN:
//		keyboardstate[event->key.keysym.scancode] = true;
//		break;
//	case SDL_KEYUP:
//		keyboardstate[event->key.keysym.scancode] = false;
//		break;
//	}
//}

void Pong::handleInputs()
{
	keyboardstate = SDL_GetKeyboardState(NULL);
}

void Pong::update()
{
	if (state == STATE_STOPPED)
	{
		reset();
	}
	else
	{
		if (keyboardstate[SDL_SCANCODE_W])
		{
			leftPaddle.moveUp();
		}
		if (keyboardstate[SDL_SCANCODE_S])
		{
			leftPaddle.moveDown();
		}
		if (keyboardstate[SDL_SCANCODE_UP])
		{
			rightPaddle.moveUp();
		}
		if (keyboardstate[SDL_SCANCODE_DOWN])
		{
			rightPaddle.moveDown();
		}

		ball.move();
		handleCollisions();
	}
}

void Pong::render()
{
	renderBackground();
	renderPaddles();
	renderBall();

	SDL_RenderPresent(App::getRenderer());
}

void Pong::renderBackground()
{
	SDL_SetRenderDrawColor(App::getRenderer(), 50, 50, 50, 255);
	SDL_RenderClear(App::getRenderer());
}

void Pong::renderBall()
{
	SDL_SetRenderDrawColor(App::getRenderer(), 255, 255, 255, 255);
	SDL_RenderFillRect(App::getRenderer(), ball.getRect());
}

void Pong::renderPaddles()
{
	SDL_SetRenderDrawColor(App::getRenderer(), 255, 255, 255, 255);
	SDL_RenderFillRect(App::getRenderer(), leftPaddle.getRect());
	SDL_RenderFillRect(App::getRenderer(), rightPaddle.getRect());
}

void Pong::renderScores()
{
	std::cout << "Left: " << leftScore << " " << "Right: " << rightScore << std::endl;
}

void Pong::increaseScore(bool giveToLeft)
{
	if (giveToLeft)
		leftScore++;
	else
		rightScore++;
}

void Pong::handleCollisions()
{
	if (ball.y() <= 0 ||
		ball.y()+ball.ballSize >= App::WINDOW_HEIGHT) //if ball touches top or bottom sides
	{
		ball.bounceWall();
	}
	else if (ball.velocityX < 0) //if ball is going left
	{
		if (ball.x() <= 0) //if ball touches left side
		{
			ball.reset();
			increaseScore(false);
			renderScores(); //eventually use this in render() but we need to display actual text in window
		}
		else if (ball.x() <= leftPaddle.x()+leftPaddle.paddleWidth &&
			ball.x()+ball.ballSize >= leftPaddle.x() &&
			ball.y() >= leftPaddle.y() &&
			ball.y() <= leftPaddle.y()+leftPaddle.paddleHeight) //if ball touches left paddle
		{
			ball.bouncePaddle(&leftPaddle);
		}
	}
	else if (ball.velocityX > 0) //if ball is going right
	{
		if (ball.x()+ball.ballSize >= App::WINDOW_WIDTH) //if ball touhces right side
		{
			ball.reset();
			increaseScore(true);
			renderScores(); //
		}
		else if (ball.x()+ball.ballSize >= rightPaddle.x() &&
			ball.x() <= rightPaddle.x()+rightPaddle.paddleWidth &&
			ball.y() >= rightPaddle.y() &&
			ball.y() <= rightPaddle.y()+rightPaddle.paddleHeight) //if ball touches right paddle
		{
			ball.bouncePaddle(&rightPaddle);
		}
	}
}

void Pong::reset()
{
	leftPaddle.resetPos();
	rightPaddle.resetPos();
	state = STATE_RUNNING;
}