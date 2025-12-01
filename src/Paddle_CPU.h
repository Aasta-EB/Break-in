#pragma once
#include "Window.h"
#include "Paddle_1.h"
#include "Paddle_2.h"
#include "Ball.h"
#include "Blocks.h"
#include "FunDrop.h"
#include "Vector2d.h"

#include <raylib.h>
#include <raymath.h>
#include <iostream>

extern Ball ball;
extern Ball ballTwo;
extern FunDrop fundrop;

class Paddle_CPU
{
public:
	
	Color CornflowerBlue{100, 143, 255, 255};
	float height = 120;
	float width = 25;
	float x = 10;
	float y = 900 / 2 - height / 2;
	float speed = 6.25;
	
	
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
	
	void StartSlowDown()
	{
		paddleSlowDown = true;
		AnimTime = 0.0f;
	}
	
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


	void Draw()
	{
		ballTwo.Draw();
		DrawRectangleRounded(Rectangle{x, y, width, height}, 0.8, 0, CornflowerBlue);
	}


	void Update()
	{
		ballTwo.Shoot();

		if (paddleSlowDown)
		{
			AnimTime += GetFrameTime();

			// Speed set slower
			speed = 4;

			if (AnimTime >= paddleSlowedDuration)
			{
				speed = 6.25;
				paddleSlowDown = false;
			}
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
				speed = 6.25;
				paddleSpeedUp = false;
			}
		}




		Vector2d playerPos{ x, y };
		Vector2d ball1Pos{ ball.x, ball.y };
		Vector2d ball2Pos{ ballTwo.x, ballTwo.y };

		// Pick the closest ball using Vector2d distance
		float dist1 = playerPos.DistanceToTarget(ball1Pos);
		float dist2 = playerPos.DistanceToTarget(ball2Pos);

		Vector2d targetBall = (dist1 <= dist2) ? ball1Pos : ball2Pos;

		float paddleCenterY = y + height / 2;

		if (paddleCenterY > targetBall.y)
			y -= speed; 
		else if (paddleCenterY < targetBall.y)
			y += speed;  

		if (y < 0) y = 0;
		if (y + height > 900) y = 900 - height;
	}



	void ResetPaddleCPU()
	{
		x = 10;
		y = 900 / 2 - height / 2;

		height = 120;
		speed = 6.25;

		paddleSize = false;
		paddleSpeedUp = false;
		paddleSlowDown = false;
		
	}

};