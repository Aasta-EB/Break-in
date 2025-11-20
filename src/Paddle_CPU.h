#pragma once
#include "Window.h"
#include "Paddle_1.h"
#include "Paddle_2.h"
#include "Ball.h"
#include "Blocks.h"

#include <raylib.h>
#include <iostream>

extern Ball ball;
extern Ball ballTwo;

class Paddle_CPU
{
public:

	float height = 120;
	float width = 25;
	float x = 10;
	float y = 900 / 2 - height / 2;
	float speed = 6.25;

	void Draw()
	{
		ballTwo.Draw();
		DrawRectangleRounded(Rectangle{x, y, width, height}, 0.8, 0, WHITE);
	}


	void Update()
	{
		ballTwo.Shoot();

		if (y + height / 2 > ballTwo.y)
		{
			y = y - speed;
		}

		if (y + height / 2 <= ballTwo.y)
		{
			y = y + speed;
		}
	}


};