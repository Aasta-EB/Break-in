#pragma once
#include "Window.h"
#include "Paddle_2.h"
#include "Paddle_CPU.h"
#include "Ball.h"
#include "Blocks.h"
#include "FunDrop.h"

#include <raylib.h>
#include <iostream>
#include <vector>

extern Ball ball;
extern Ball ballTwo;
extern FunDrop fundrop;
extern Paddle_2 playerTwo;
extern Paddle_CPU cpu;

class Paddle_1
{
public:
	//float x, y;
	//float width, height;
	//int speed

	Color OrangeRed{ 254, 97, 0, 255 };

	float width = 25;
	float height = 120;
	float x = 1400 - 35; 
	float y = 900 / 2 - 60;
	float speed = 6;

	//Variables for math related FunDrops
	bool sizeAnimating = false;
	float sizeAnimTime = 0.0f;

	float paddleBaseHeight = 120;
	float paddleMaxHeight = 300;
	float paddleAnimDuration = 10.0f;

	
	void StartPaddleEnlarge()
	{
		sizeAnimating = true;
		sizeAnimTime = 0.0f; 
	}


	void Draw()
	{
		DrawRectangleRounded(Rectangle{ x, y, width, height}, 0.8, 0, OrangeRed);
	}


	void SpeedUp()
	{
		speed = 10;
	}

	void Update()
	{


		// Controlls for player movement
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
			ball.Shoot();

		}

		// Paddle Size upgrade animation
		if (sizeAnimating)
		{
			sizeAnimTime += GetFrameTime();

			float t = sizeAnimTime;
			float T = paddleAnimDuration;
			float H0 = paddleBaseHeight;
			float Hmax = paddleMaxHeight;
			float A = Hmax - H0;

			if (t >= T)
			{
				t = T;
				sizeAnimating = false;
			}

			// h(t) = H0 + A * sin(pi * t / T)
			height = H0 + A * sinf(PI * (t / T));
			
			// Re-center the paddle during animation
			if (sizeAnimTime < GetFrameTime()) 
			{
				y -= 0.5f * (height - paddleBaseHeight);  
			}
		}

		for (Drop& drop : fundrop.drops)
		{
		if (!drop.active)
		{
			continue;
		}

		if (CheckCollisionCircleRec(drop.position, 25, Rectangle{ x, y, width, height }))
		{
			FunUpgrade funShowtime = fundrop.RandomUpgrade();
			drop.active = false;

			switch (funShowtime)
			{
			case ENLARGE_BALL:
				ballTwo.StartEnlarge();
				break;
			case ENLARGE_PADDLE:
				StartPaddleEnlarge();
				break;
			case SPEED_BALL:
				ballTwo.ApplySpeedBoost(1.15f, 6.0f);
				break;
			case SPEED_OPPONENT:
				playerTwo.Slowed();
				cpu.Slowed();
				break;
			case SPEED_SELF:
				SpeedUp();
				break;
			default:
				break;
			}
		}
		}

	}



	void ResetPaddle()
	{
		float x = 1400 - 35; 
		float y = 900 / 2 - 60;

	}


};