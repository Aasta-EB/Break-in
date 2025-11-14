#pragma once
#include "Window.h"
#include "Paddle_2.h"
#include "Paddle_CPU.h"
#include "Ball.h"
#include "Blocks.h"

#include <raylib.h>
#include <iostream>

extern Ball ball;

class Paddle_1
{
public:
	//float x, y;
	//float width, height;
	//int speed;

	float width = 25;
	float height = 120;
	float x = 1400 - 35; // Should have adaptable variables
	float y = 900 / 2 - 60;
	float speed = 6;

	void Draw()
	{
		ball.Draw();
		DrawRectangleRounded(Rectangle{ x, y, width, height}, 0.8, 0, WHITE);
	}

	void Update()
	{
		if (IsKeyDown(KEY_UP))
		{
			y = y - speed;
		}

		if (IsKeyDown(KEY_DOWN))
		{
			y = y + speed;
		}

		if (y <= 0)
		{
			y = 0;
		}

		if (y + height >= GetScreenHeight())
		{
			y = GetScreenHeight() - height;
		}

		if (IsKeyDown(KEY_RIGHT_SHIFT))
		{
			ball.has_been_shot = true;

		}


	}
};