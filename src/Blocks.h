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
				Brick blocks = {{j * (brickWidth + 5) + 1400 / 2 - 68, i * (brickHeight + 8), brickWidth, brickHeight}, true};
				bricks.push_back(blocks);
			}
		}
	}


	void Draw()
	{
		for (int index = 0; index < bricks.size(); index++) {

			if (!bricks.at(index).active)
			{
				continue;
			}

			Brick currentBrix = bricks.at(index);
			if (currentBrix.active)
			{
				DrawRectangle(currentBrix.position.x - brickWidth  / 2, currentBrix.position.y - brickHeight / 2, brickWidth, brickHeight, RED);
			}
		}
	}
};

