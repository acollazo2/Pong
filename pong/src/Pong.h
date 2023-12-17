#pragma once

#include <SDL2/SDL.h>
#include "Paddle.h"
#include "Ball.h"

class Pong
{
public:
	enum GAME_STATE {STATE_STOPPED = 0, STATE_RUNNING};

	Pong();
	void handleInputs();
	void update();
	void render();

private:
	void renderBackground();
	void renderBall();
	void renderPaddles();
	void renderScores();
	void increaseScore(bool giveToLeft);
	void handleCollisions();
	void reset();


private:
	GAME_STATE state;

	const Uint8* keyboardstate;
	
	Paddle leftPaddle;
	Paddle rightPaddle;
	Ball ball;
	int leftScore = 0;
	int rightScore = 0;
};