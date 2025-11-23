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
extern FunDrop fundrop;

class Paddle_1
{
public:
	//float x, y;
	//float width, height;
	//int speed

	Color OrangeRed{ 254, 97, 0, 255 };

	float width = 25;
	float height = 120;
	float x = 1400 - 35; // Should have adaptable variables
	float y = 900 / 2 - 60;
	float speed = 6;

	void Draw()
	{
		DrawRectangleRounded(Rectangle{ x, y, width, height}, 0.8, 0, OrangeRed);
	}

	void Update()
	{
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

		if (CheckCollisionCircleRec(Vector2{ fundrop.x, fundrop.y }, 25, Rectangle{ x, y, width, height }))
		{
			std::cout << "Collision!" << std::endl;
			fundrop.drawColor = ORANGE;
			FunUpgrade funShowtime = fundrop.RandomUpgrade();

			switch (funShowtime)
			{
			case ENLARGE_BALL:
				// ball.enlarge()
				break;
			case ENLARGE_PADDLE:
				//enlarge()
				break;
			default:
				break;
			}
		}


	}



	void ResetPaddle()
	{
		float x = 1400 - 35; 
		float y = 900 / 2 - 60;

	}


};