#include <raylib.h>
#include <iostream>


#include "Window.h"
#include "Blocks.h"
#include "Paddle_1.h"
#include "Paddle_2.h"
#include "Paddle_CPU.h"
#include "Ball.h"

using namespace std;


Window value;
Ball ball;
Paddle_1 player;
Paddle_2 playerTwo;
Blocks brick;

//Game state


int main()
{

	cout << "Starting the game" << endl;
	InitWindow(value.screen_width, value.screen_height, "Break-in!");
	SetTargetFPS(60);

	brick.initialize();

	while (WindowShouldClose() == false)
	{


		BeginDrawing();

		// Updating
		ball.Update();
		player.Update();
		playerTwo.Update();

		

		
			// Checking for collision player 1
			if (CheckCollisionCircleRec(Vector2{ ball.x, ball.y }, ball.radius, Rectangle{ player.x, player.y, player.width, player.height }))
			{
				ball.speed_x *= -1;
			}

			// Checking for collision player 2
			if (CheckCollisionCircleRec(Vector2{ ball.x, ball.y }, ball.radius, Rectangle{ playerTwo.x, playerTwo.y, playerTwo.width, playerTwo.height }))
			{
				ball.speed_x *= -1;
			}

			
		
		ClearBackground(BLACK);
		DrawLine(value.screen_width / 2, 0, value.screen_width / 2, value.screen_height, GRAY);
		
		//Drawing
		ball.Draw();
		player.Draw();
		playerTwo.Draw();
		brick.Draw();

		//Score text
		DrawText(TextFormat("%i", ball.playerTwo_score), value.screen_width / 4 - 20, 20, 80, WHITE);
		DrawText(TextFormat("%i", ball.player_score), 3 * value.screen_width / 4 - 20, 20, 80, WHITE);
		EndDrawing();


	}

	CloseWindow();
	return 0;
}