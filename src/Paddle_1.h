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

	void Enlarge()
	{
		height = 300;
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

		for (Drop& drop : fundrop.drops)
		{
		if (!drop.active)
		{
			continue;
		}

		if (CheckCollisionCircleRec(drop.position, 25, Rectangle{ x, y, width, height }))
		{
			fundrop.drawColor = WHITE;
			FunUpgrade funShowtime = fundrop.RandomUpgrade();
			drop.active = false;

			switch (funShowtime)
			{
			case ENLARGE_BALL:
				ball.Enlarge();
				break;
			case ENLARGE_PADDLE:
				Enlarge();
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