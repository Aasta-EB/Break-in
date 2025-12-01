#pragma once
#include "Window.h"
#include "Paddle_1.h"
#include "Paddle_CPU.h"
#include "Ball.h"
#include "Blocks.h"
#include "FunDrop.h"

#include <raylib.h>
#include <iostream>

extern Ball ballTwo;
extern FunDrop fundrop;

class Paddle_2
{
public:
	//float x, y;
	//float width, height;
	//int speed;

	Color CornflowerBlue{ 100, 143, 255, 255 };
	float width = 25;
	float height = 120;
	float x = 10;
	float y = 900 / 2 - 120 / 2;
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
		DrawRectangleRounded(Rectangle{ x, y, width, height }, 0.8, 0, CornflowerBlue);
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
			ballTwo.Shoot();

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
		x = 10;
		y = 900 / 2 - 60;
		height = 120;
		speed = 6;

		paddleSize = false;
		paddleSpeedUp = false;
		paddleSlowDown = false;
	}


};