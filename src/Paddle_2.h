#pragma once
#include "Window.h"
#include "Paddle_1.h"
#include "Paddle_CPU.h"
#include "Ball.h"
#include "Blocks.h"

#include <raylib.h>
#include <iostream>

extern Ball ballTwo;

class Paddle_2
{
public:
	//float x, y;
	//float width, height;
	//int speed;

	float width = 25;
	float height = 120;
	float x = 10;
	float y = 900 / 2 - 120 / 2;
	float speed = 6;


	void Draw()
	{

		DrawRectangleRounded(Rectangle{ x, y, width, height }, 0.8, 0, WHITE);
	}

	void Update()
	{
		if (IsKeyDown(KEY_W))
		{
			y = y - speed;
		}

		if (IsKeyDown(KEY_S))
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

		if (IsKeyDown(KEY_Q))
		{
			ballTwo.has_been_shot = true;

		}

	}

};