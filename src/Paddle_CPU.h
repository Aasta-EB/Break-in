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
	
	void Draw()
	{
		ballTwo.Draw();
		DrawRectangleRounded(Rectangle{x, y, width, height}, 0.8, 0, CornflowerBlue);
	}


	void Update()
	{
		ballTwo.Shoot();

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

	void Slowed()
	{
		speed = 3;
	}

	void ResetPaddleCPU()
	{
		float x = 10;
		float y = 900 / 2 - height / 2;

	}

};