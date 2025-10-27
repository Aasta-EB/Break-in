#pragma once
#include "Window.h"
#include "Paddle_1.h"
#include "Paddle_2.h"
#include "Paddle_CPU.h"
#include "Blocks.h"

#include <algorithm>
#include <raylib.h>
#include <iostream>
#include <string>



class Ball {
public:

	bool player_alive = true;
	bool playerTwo_alive = true;


	int player_score = 5;
	int playerTwo_score = 5;

	int radius = 15;
	float x = 1400 / 2; //needs to fetch window width and window height from window class
	float y = 900 / 2;
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

		if (x + radius >= 1400)

		{
			player_score--;
			player_score = std::max(player_score, 0);

			if (player_score == 0)
			{
				DrawText("Left Player Wins", 50, GetScreenHeight() / 2 - 30, 60, YELLOW);
			}

			else {
				ResetBall();
			}
		}

		if (x - radius <= 0)
		
		{
			playerTwo_score--;
			playerTwo_score = std::max(playerTwo_score, 0);

			if (playerTwo_score == 0)
			{
				DrawText("Right Player Wins", GetScreenWidth() / 2 + 100, GetScreenHeight() / 2 - 30, 60, YELLOW);
			}

			else {
				ResetBall();
			}



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
