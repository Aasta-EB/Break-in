#pragma once
#include "Window.h"
#include "Paddle_1.h"
#include "Paddle_2.h"
#include "Paddle_CPU.h"
#include "Blocks.h"
#include "FunDrop.h"
#include "Vector2d.h"

#include <algorithm>
#include <raylib.h>
#include <iostream>
#include <string>


extern FunDrop fundrop;
extern Blocks blocks;

class Ball {
public:

	int radius = 15;

	float x = 1400 / 2;
	float y = 900 / 2;
	float default_speed_x = 7;
	float default_speed_y = 7;
	float speed_x = default_speed_x;
	float speed_y = default_speed_y;
	Color drawColor = WHITE;
	bool has_been_shot = false;



	// ENLARGE_BALL
	bool sizeAnimating = false;
	float sizeAnimTime = 0.0f;

	float animationDuration = 10.0f;   
	int baseRadius = 15;               
	int maxRadius = 30;                

	// SPEED_BALL
	Vector2d baseVelocity;   // Stores original speed vector
	bool speedBoostActive = false;
	float boostTimer = 0.0f;
	float speedMultiplier = 1.0f;
	float max_speed = 9.f;


	Ball(int xPosition, int yPosition, Color ballColor)
	{
		x = xPosition;
		y = yPosition;
		drawColor = ballColor;

	}

	void StartEnlarge()
	{
		sizeAnimating = true;
		sizeAnimTime = 0.0f;
	}


	void ApplySpeedBoost(float multiplier, float duration)
	{
		speedBoostActive = true;
		speedMultiplier = multiplier;
		boostTimer = duration;
	}


	void Draw()
	{
		DrawCircle(x, y, radius, drawColor);
	}

	void Update(int& player_score, int& playerTwo_score, int heldPositionX, int heldPositionY)
	{

		//Updating for math Upgrades in FunDrop
		if (sizeAnimating)
		{
			sizeAnimTime += GetFrameTime();

			float t = sizeAnimTime;
			float T = animationDuration;
			float R0 = baseRadius;
			float Rmax = maxRadius;
			float A = Rmax - R0;

			if (t >= T)
			{
				t = T;
				sizeAnimating = false;
			}

			// Radius function: r(t) = R0 + A * sin(pi * t / T)
			radius = R0 + A * sinf(PI * t / T);
		}

		// Shooting the ball
		if (!has_been_shot)
		{
			x = heldPositionX;
			y = heldPositionY;
			return;
		}

		//SPEED_BALL
		if (speedBoostActive)
		{
			boostTimer -= GetFrameTime();

			// Scale the original base velocity
			Vector2d boosted = baseVelocity.ScaleVector(speedMultiplier);
			
			speed_x = std::min(max_speed, std::max(boosted.x, -max_speed));
			speed_y = std::min(max_speed, std::max(boosted.y, -max_speed));

			if (boostTimer <= 0.0f)
			{
				speedBoostActive = false;
				speedMultiplier = 1.0f;

				// Restore original speed
				speed_x = speed_x < 0 ?  -default_speed_x: default_speed_x;
				speed_y = speed_y < 0 ? -default_speed_y: default_speed_y;
			}
		}

		x += speed_x;
		y += speed_y;

		if (y + radius >= GetScreenHeight() || y - radius <= 0)
		{
			speed_y *= -1;;
			baseVelocity = Vector2d(speed_x, speed_y);

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

		//Collision with brick
		for (int index = 0; index < blocks.bricks.size(); index++)
		{
			Brick& brick = blocks.bricks.at(index);
			if (!brick.active)
			{
				continue;
			}

			// Hit below
			if (((y - radius) <= (brick.position.y + blocks.brickHeight / 2)) &&
				((y - radius) > (brick.position.y + blocks.brickHeight / 2 + speed_y)) &&
				((fabs(x - brick.position.x)) < (blocks.brickWidth / 2 + radius * 2 / 3)) && (speed_y < 0))
			{
				brick.active = false;
				speed_y *= -1;
				baseVelocity = Vector2d(speed_x, speed_y);
			}


			// Hit above
			else if (((y + radius) >= (brick.position.y - blocks.brickHeight / 2)) &&
				((y + radius) < (brick.position.y - blocks.brickHeight / 2 + speed_y)) &&
				((fabs(x - brick.position.x)) < (blocks.brickWidth / 2 + radius * 2 / 3)) && (speed_y > 0))
			{
				brick.active = false;
				speed_y *= -1;
				baseVelocity = Vector2d(speed_x, speed_y);
			}


			// Hit left
			else if (((x + radius) >= (brick.position.x - blocks.brickWidth / 2)) &&
				((x + radius) < (brick.position.x - blocks.brickWidth / 2 + speed_x)) &&
				((fabs(y - brick.position.y)) < (blocks.brickHeight / 2 + radius * 2 / 3)) && (speed_x > 0))
			{
				brick.active = false;
				speed_x *= -1;
				baseVelocity = Vector2d(speed_x, speed_y);

				fundrop.Spawn(brick.position.x - blocks.brickWidth / 2, brick.position.y - blocks.brickHeight / 2, -1);

			}


			// Hit right
			else if (((x + radius) <= (brick.position.x + blocks.brickWidth)) &&
				((x + radius) > (brick.position.x + blocks.brickWidth / 2 + speed_x)) &&
				((fabs(y - brick.position.y)) < (blocks.brickHeight / 2 + radius * 2 / 3)) && (speed_x < 0))
			{
				brick.active = false;
				speed_x *= -1;
				baseVelocity = Vector2d(speed_x, speed_y);


				fundrop.Spawn(brick.position.x - blocks.brickWidth / 2, brick.position.y - blocks.brickHeight / 2, 1);
			}

			

		}

	}



	void Shoot()
	{
		baseVelocity = Vector2d(speed_x, speed_y);
		has_been_shot = true;

	}



	// Reset position
	void ResetBall(int heldPositionX, int heldPositionY)
	{
		has_been_shot = false;
		x = heldPositionX;
		y = heldPositionY;
		
		speed_x = default_speed_x;
		speed_y = default_speed_y;
	}




};
