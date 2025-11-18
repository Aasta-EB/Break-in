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

extern Blocks brick;

class Ball {
public:


	int radius = 15;

	float x = 1400 / 2; //needs to fetch window width and window height from window class
	float y = 900 / 2;
	int speed_x = 7;
	int speed_y = 7;
	bool has_been_shot = false;

	Ball(int xPosition, int yPosition)
	{
		x = xPosition;
		y = yPosition;

	}


	void Draw()
	{
		DrawCircle(x, y, radius, WHITE);
	}

	void Update(int& player_score, int& playerTwo_score, int heldPositionX, int heldPositionY)
	{
		if (!has_been_shot)
		{
			x = heldPositionX;
			y = heldPositionY;
			return;
		}

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
				ResetBall(heldPositionX, heldPositionY);
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
				ResetBall(heldPositionX, heldPositionY);
			}



		}

		for (Brick b : brick.bricks)
		{
			if (!b.active)
			{
				continue;
			}

			// Hit below
			if (((y - radius) <= (b.position.y + brick.brickHeight / 2)) &&
				((y - radius) > (b.position.y + brick.brickHeight / 2 + speed_y)) &&
				((fabs(x - b.position.x)) < (brick.brickWidth / 2 + radius * 2 / 3)) && (speed_y < 0))
			{
				b.active = false;
				speed_y *= -1;
			}


			// Hit above
			else if (((y + radius) >= (b.position.y - brick.brickHeight / 2)) &&
				((y + radius) < (b.position.y - brick.brickHeight / 2 + speed_y)) &&
				((fabs(x - b.position.x)) < (brick.brickWidth / 2 + radius * 2 / 3)) && (speed_y > 0))
			{
				b.active = false;
				speed_y *= -1;
			}


			// Hit left
			else if (((x + radius) >= (b.position.x - brick.brickWidth / 2)) &&
				((x + radius) < (b.position.x - brick.brickWidth / 2 + speed_x)) &&
				((fabs(y - b.position.y)) < (brick.brickHeight / 2 + radius * 2 / 3)) && (speed_x > 0))
			{
				b.active = false;
				speed_x *= -1;
			}


			// Hit right
			else if (((x + radius) <= (b.position.x - brick.brickWidth / 2)) &&
				((x + radius) > (b.position.x - brick.brickWidth / 2 + speed_x)) &&
				((fabs(y - b.position.y)) < (brick.brickHeight / 2 + radius * 2 / 3)) && (speed_x < 0))
			{
				b.active = false;
				speed_x *= -1;
			}
		}

	}



	void Shoot()
	{
		
		has_been_shot = true;

	}



	// needs breakout reset position
	void ResetBall(int heldPositionX, int heldPositionY)
	{
		has_been_shot = false;
		x = heldPositionX;
		y = heldPositionY;

		int speed_choices[2] = { -1, 1 };
		speed_x *= speed_choices[GetRandomValue(0, 1)];
		speed_y *= speed_choices[GetRandomValue(0, 1)];
	}

};
