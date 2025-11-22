#pragma once
#include "Window.h"
#include "Paddle_1.h"
#include "Paddle_2.h"
#include "Ball.h"
#include "Blocks.h"
#include "FunDrop.h"

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


		Vector2 playerPostion{ x, y };
		Vector2 ballOnePosition{ ball.x, ball.y };
		Vector2 ballTwoPosition{ ballTwo.x, ballTwo.y };

		float distanceToBallONE = Vector2Distance(playerPostion, ballOnePosition);
		float distanceToBallTWO = Vector2Distance(playerPostion, ballTwoPosition);

		if (distanceToBallONE <= distanceToBallTWO)
		{
			if (y + height / 2 > ball.y)
			{
				y = y - speed;
			}

			if (y + height / 2 <= ball.y)
			{
				y = y + speed;
			}

		}

		else
		{
			if (y + height / 2 > ballTwo.y)
			{
				y = y - speed;
			}

			if (y + height / 2 <= ballTwo.y)
			{
				y = y + speed;
			}
		}

		
	}

	void ResetPaddleCPU()
	{
		float x = 10;
		float y = 900 / 2 - height / 2;

	}

};