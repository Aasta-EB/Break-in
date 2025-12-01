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
#include <algorithm>
#include <string>

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
	Color WarmYellow{ 255,176,0, 255 };

	float width = 25;
	float height = 120;
	float x = 1400 - 35; 
	float y = 900 / 2 - 60;
	float speed = 6;

	//Variables for math related FunDrops
	float AnimTime = 0.0f;
	float paddleEnlargeDuration = 10.0f;
	float paddleSpedUpDuration = 10.0f;
	float paddleSlowedDuration = 1.5f;
	

	// Boolean checks for if Fundrop animation is to start
	bool paddleSpeedUp = false;
	bool paddleSlowDown = false;
	bool paddleSize = false;


	// Variables for Paddle_enlarge
	float paddleBaseHeight = 120;
	float paddleMaxHeight = 300;

	// Variables for Paddle_speedup
	float paddleBaseSpeed = 6;
	float paddleMaxSpeed = 9;

	void StartPaddleEnlarge()
	{
		paddleSize = true;
		AnimTime = 0.0f; 
	}

	void StartSpeedUp()
	{
		paddleSpeedUp = true;
		AnimTime = 0.0f;
	}

	void StartSlowDown()
	{
		paddleSlowDown = true;
		AnimTime = 0.0f;
	}

	void Draw()
	{
		DrawRectangleRounded(Rectangle{ x, y, width, height}, 0.8, 0, WarmYellow);
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

		if (paddleSize)
		{
			AnimTime += GetFrameTime();

			float t = AnimTime;
			if (t >= paddleEnlargeDuration)
			{
				t = paddleEnlargeDuration;
				paddleSize = false;
			}

			float progress = t / paddleEnlargeDuration;
			float amount = std::sinf(progress * PI);

			height = paddleBaseHeight + (paddleMaxHeight - paddleBaseHeight) * amount;

			if (AnimTime < GetFrameTime()) 
			{
				y -= 0.5f * (height - paddleBaseHeight);  
			}
		}

		if (paddleSpeedUp)
		{
			AnimTime += GetFrameTime();

			// Speed set faster
			speed = 9;

			if (AnimTime >= paddleSpedUpDuration)
			{
				speed = 6;
				paddleSpeedUp = false;
			}
		}

		if (paddleSlowDown)
		{
			AnimTime += GetFrameTime();

			// Speed set slower
			speed = 4;

			if (AnimTime >= paddleSlowedDuration)
			{
				speed = 6;
				paddleSlowDown = false;
			}
		}

	}



	void ResetPaddle()
	{
		x = 1400 - 35; 
		y = 900 / 2 - 60;
		height = 120;
		speed = 6;

		paddleSize = false;
		paddleSpeedUp = false;
		paddleSlowDown = false;
	}


};