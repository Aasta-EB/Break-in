#include <raylib.h>
#include <iostream>


#include "Window.h"
#include "Blocks.h"
#include "Paddle_1.h"
#include "Paddle_2.h"
#include "Paddle_CPU.h"
#include "Ball.h"

using namespace std;


int player_score = 5;
int playerTwo_score = 5;

Window value;
Paddle_1 player;
Paddle_2 playerTwo;
Ball ball(player.x - 30, player.y);
Ball ballTwo(playerTwo.x + 30, playerTwo.y);
Blocks blocks;

//Game state


int main()
{

	cout << "Starting the game" << endl;
	InitWindow(value.screen_width, value.screen_height, "Break-in!");

	SetTargetFPS(60);

	blocks.initialize();

	while (WindowShouldClose() == false)
	{


		BeginDrawing();

		// Updating
		player.Update();
		playerTwo.Update();
		ball.Update(player_score, playerTwo_score, player.x - 20, player.y + player.height/2);
		ballTwo.Update(player_score, playerTwo_score, playerTwo.x + playerTwo.width + 20, playerTwo.y + playerTwo.height/2);
	

		

		
		// Checking for collision player 1
		if (CheckCollisionCircleRec(Vector2{ ball.x, ball.y }, ball.radius, Rectangle{ player.x, player.y, player.width, player.height }))
		{
			if (ball.Can_Bounce())
			{
				ball.speed_x *= -1;
				ball.Toggle_Bounce();
			}
			
		}
		else
		{
			if (!ball.Can_Bounce())
			{
				ball.Toggle_Bounce();
			}
		}


		if (CheckCollisionCircleRec(Vector2{ ballTwo.x, ballTwo.y }, ballTwo.radius, Rectangle{ player.x, player.y, player.width, player.height }))
		{
	
				if (ballTwo.Can_Bounce())
				{
					ballTwo.speed_x *= -1;
					ballTwo.Toggle_Bounce();
				}

		
		else
		{
			if (!ballTwo.Can_Bounce())
			{
				ballTwo.Toggle_Bounce();
			}
		}

		}

		// Checking for collision player 2
		if (CheckCollisionCircleRec(Vector2{ ball.x, ball.y }, ball.radius, Rectangle{ playerTwo.x, playerTwo.y, playerTwo.width, playerTwo.height }))
		{
			if (ball.Can_Bounce())
			{
				ball.speed_x *= -1;
				ball.Toggle_Bounce();
			}

		}
		else
		{
			if (!ball.Can_Bounce())
			{
				ball.Toggle_Bounce();
			}
		}


		if (CheckCollisionCircleRec(Vector2{ ballTwo.x, ballTwo.y }, ballTwo.radius, Rectangle{ playerTwo.x, playerTwo.y, playerTwo.width, playerTwo.height }))
		{
			if (ballTwo.Can_Bounce())
			{
				ballTwo.speed_x *= -1;
				ballTwo.Toggle_Bounce();
			}


			else
			{
				if (!ballTwo.Can_Bounce())
				{
					ballTwo.Toggle_Bounce();
				}
			}
		}
			
		
		ClearBackground(BLACK);
		DrawLine(value.screen_width / 2, 0, value.screen_width / 2, value.screen_height, GRAY);
		
		//Drawing
		player.Draw();
		playerTwo.Draw();
		ball.Draw();
		ballTwo.Draw();
		blocks.Draw();

		//Score text
		DrawText(TextFormat("%i", playerTwo_score), value.screen_width / 4 - 20, 20, 80, WHITE);
		DrawText(TextFormat("%i", player_score), 3 * value.screen_width / 4 - 20, 20, 80, WHITE);
		EndDrawing();


	}

	CloseWindow();
	return 0;
}