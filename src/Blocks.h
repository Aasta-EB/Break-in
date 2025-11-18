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

typedef struct Brick {
	Rectangle position;
	bool active;
} Brick;

class Blocks
{
public:

	int rows = 15;
	int columns = 4;
	int brickWidth = 40;
	int brickHeight = 70;
	std::vector<Brick> bricks;

	void initialize()
	{
		bricks.clear(); //clear existing bricks
		for (int i = 0; i < rows; i++)
		{
			for (int j = 0; j < columns; j++)
			{
				Brick brick = {{j * (brickWidth + 5) + 1400 / 2 - 88, i * (brickHeight + 5), brickWidth, brickHeight}, true};
				bricks.push_back(brick);
			}
		}
	}


	void Draw()
	{
		for (Brick b : bricks) {

			if (b.active)
			{
				DrawRectangle(b.position.x, b.position.y, brickWidth, brickHeight, RED);
			}
		}
	}
};

