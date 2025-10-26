#pragma once
#include "Window.h"
#include "Paddle_1.h"
#include "Paddle_2.h"
#include "Paddle_CPU.h"
#include "Blocks.h"

#include <raylib.h>
#include <iostream>


class Ball {
public:


	int player_score = 0;
	int playerTwo_score = 0;

	int radius = 15;
	float x = GetScreenWidth() / 2; //needs to fetch window width and window height from window class
	float y = GetScreenHeight() / 2;
	int speed_x = 7;
	int speed_y = 7;


	void Draw()
	{
		DrawCircle(x, y, radius, WHITE);
	}
	void Update()
	{
		x += speed_x;
		y += speed_y;

		if (y + radius >= GetScreenHeight() || y - radius <= 0)
		{
			speed_y *= -1;;

		}

		if (x + radius >= GetScreenWidth())

		{
			playerTwo_score++;
			ResetBall();
		}
		if (x - radius <= 0)
		{
			player_score++;
			ResetBall();
		}

	}

	// needs breakout reset position
	void ResetBall()
	{
		x = GetScreenWidth() / 2;
		y = GetScreenHeight() / 2;

		int speed_choices[2] = { -1, 1 };
		speed_x *= speed_choices[GetRandomValue(0, 1)];
		speed_y *= speed_choices[GetRandomValue(0, 1)];
	}

};
