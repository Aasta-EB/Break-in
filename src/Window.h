#pragma once
#include "Paddle_1.h"
#include "Paddle_2.h"
#include "Paddle_CPU.h"
#include "Ball.h"
#include "Blocks.h"
#include "FunDrop.h"

#include <raylib.h>
#include <iostream>


extern Paddle_1 player;
extern Paddle_2 playerTwo;
extern Paddle_CPU cpu;
extern FunDrop fundrop;
extern Ball ball;
extern Ball ballTwo;
extern Blocks blocks;

class Window
{
public:

int screen_width = 1400;
int screen_height = 900;

void CheckFundropCollision()
{

	for (Drop& drop : fundrop.drops)
	{
		if (!drop.active)
		{
			continue;
		}

		if (CheckCollisionCircleRec(drop.position, 25, { playerTwo.x, playerTwo.y, playerTwo.width, playerTwo.height }) or CheckCollisionCircleRec(drop.position, 25, { cpu.x, cpu.y, cpu.width, cpu.height }))
		{
			FunUpgrade funShowtime = fundrop.RandomUpgrade();
			drop.active = false;

			switch (funShowtime)
			{
			case ENLARGE_BALL:
				ball.StartEnlarge();
				break;
			case ENLARGE_PADDLE:
				playerTwo.StartPaddleEnlarge();
				cpu.StartPaddleEnlarge();
				break;
			case SPEED_BALL:
				ball.ApplySpeedBoost(1.10f, 6.0f);
				break;
			case SPEED_OPPONENT:
				player.StartSlowDown();
				break;
			case SPEED_SELF:
				playerTwo.StartSpeedUp();
				cpu.StartSpeedUp();
				break;
			default:
				break;
			}
		}

		if (CheckCollisionCircleRec(drop.position, 25,{ player.x, player.y, player.width, player.height}))
		{
			FunUpgrade funShowtime = fundrop.RandomUpgrade();
			drop.active = false;

			switch (funShowtime)
			{
			case ENLARGE_BALL:
				ballTwo.StartEnlarge();
				break;
			case ENLARGE_PADDLE:
				player.StartPaddleEnlarge();
				break;
			case SPEED_BALL:
				ballTwo.ApplySpeedBoost(1.10f, 6.0f);
				break;
			case SPEED_OPPONENT:
				playerTwo.StartSlowDown();
				cpu.StartSlowDown();
				break;
			case SPEED_SELF:
				player.StartSpeedUp();
				break;
			default:
				break;
			}
		}
	}
}

};

