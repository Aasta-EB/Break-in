#pragma once
#include "Window.h"
#include "Paddle_1.h"
#include "Paddle_2.h"
#include "Paddle_CPU.h"
#include "Ball.h"
#include <string>
#include <vector>

#include <raylib.h>
#include <iostream>

//extern Ball ball;

class Blocks
{
//public:
//
//	int rows = 15;
//	int columns = 4;
//	int brickWidth = 20;
//	int brickHeight = 60;
//	std::vector<Rectangle> bricks;
//
//	void initialize()
//	{
//		bricks.clear(); //clear existing bricks
//		for (int i = 0; i < rows; i++)
//		{
//			for (int j = 0; j < columns; j++)
//			{
//				Rectangle brick = { j * (brickWidth + 5) + 40, i * (brickHeight + 5) + 40, brickHeight, brickHeight };
//				bricks.push_back(brick);
//			}
//		}
//
//		for (auto it = bricks.begin(); it != bricks.end();)
//			if (CheckCollisionCircleRec(Vector2{ ball.x, ball.y }, ball.radius, *it))
//			{
//				ball.speed_x *= -1;
//				it = bricks.erase(it);
//				score += 10;
//			}
//			else {
//				++it;
//			}
//	}

};

