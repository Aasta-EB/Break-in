#include <raylib.h>
#include <iostream>
#include <cmath> 

#include "Window.h"
#include "Blocks.h"
#include "Paddle_1.h"
#include "Paddle_2.h"
#include "Paddle_CPU.h"
#include "FunDrop.h"
#include "Ball.h"

using namespace std;

//Classes
Window value;
Paddle_1 player;
Paddle_2 playerTwo;
Paddle_CPU cpu;
FunDrop fundrop;
Ball ball(player.x - 50, player.y, WarmYellow);
Ball ballTwo(playerTwo.x + 50, playerTwo.y, CornflowerBlue);
Blocks blocks;

int main()
{
	InitWindow(screen_width, screen_height, "Break-in!");

	SetTargetFPS(60);

	blocks.initialize();

	while (WindowShouldClose() == false)
	{
		value.CheckGameState();

		BeginDrawing();

		value.CheckPaddleCollision();
	
		ClearBackground(DarkMaroon);

		value.HandleGameStates();

		EndDrawing();
	}

	CloseWindow();
	return 0;
}