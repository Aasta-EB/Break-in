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


//Game state
enum GameState
{
	MENU, // single player or multiplayer, esc
	GAMEPLAY_MULTI,
	GAMEPLAY_CPU,
	PAUSE_MULTI, // space to pause
	PAUSE_CPU,
	GAMEOVER //go from game over to menu
};

GameState currentGameState = MENU;



//variables
int player_score = 100;
int playerTwo_score = 100;


//Color
Color CornflowerBlue{ 100, 143, 255, 255 };
Color OrangeRed{ 254, 97, 0, 255 };

//Classes
Window value;
Paddle_1 player;
Paddle_2 playerTwo;
Paddle_CPU cpu;
FunDrop fundrop;
Ball ball(player.x - 50, player.y, OrangeRed);
Ball ballTwo(playerTwo.x + 50, playerTwo.y, CornflowerBlue);
Blocks blocks;


// Sinus Wave Movement Variables
float sinusBallX = 0.0f;            // Initial X position (start from left side)
float sinusBallY = value.screen_height / 2;   // Initial Y position
float amplitude = 100.0f;                     // How high/low the ball moves vertically
float frequency = 1.f;                       // How fast the ball oscillates vertically
float speed = 2.0f;                          // Horizontal speed of the ball
float sinusTime = 0.0f;                      // Time tracking for the sine wave


// Resetting the game
void ResetGame()
{
	player_score = 100;
	playerTwo_score = 100;
	ball.ResetBall(player.x - 50, player.y);
	ballTwo.ResetBall(playerTwo.x + 50, playerTwo.y);
	player.ResetPaddle();
	playerTwo.ResetPaddleTwo();
	cpu.ResetPaddleCPU();
	blocks.initialize();

}


int main()
{

	cout << "Starting the game" << endl;
	InitWindow(value.screen_width, value.screen_height, "Break-in!");

	SetTargetFPS(60);

	blocks.initialize();

	while (WindowShouldClose() == false)
	{
		// Update logic for the current state
		switch (currentGameState)
		{
		case MENU:
			// Handle menu input, update menu elements
			if (IsKeyPressed(KEY_ENTER)) currentGameState = GAMEPLAY_MULTI;
			if (IsKeyPressed(KEY_C)) currentGameState = GAMEPLAY_CPU;

			// Sinus wave movement for the ball in the menu
			sinusTime += GetFrameTime();  // Increment time with each frame

			// Horizontal movement
			sinusBallX += speed;  // Move the ball horizontally to the right

			// If the ball moves off the screen to the right, reset its position to the left
			if (sinusBallX > value.screen_width + 20)
				sinusBallX = -20;

			// Vertical sinusoidal movement
			sinusBallY = (value.screen_height / 2) + amplitude * sinf(frequency * sinusTime);  // Update y position of the ball

			break;
	
		case GAMEPLAY_MULTI:
			// Handle player input, update game logic, check for game over
			if (IsKeyPressed(KEY_SPACE)) currentGameState = PAUSE_MULTI;
			if (IsKeyPressed(KEY_M)) currentGameState = MENU;
			break;

		case GAMEPLAY_CPU:
			// Handle player input, update game logic, check for game over
			if (IsKeyPressed(KEY_SPACE)) currentGameState = PAUSE_CPU;
			if (IsKeyPressed(KEY_M)) currentGameState = MENU;
			if (player_score == 0 or playerTwo_score == 0)
			{
				currentGameState = GAMEOVER;
			}
			
			// ... if game over condition met ...
			// currentGameState = STATE_GAMEOVER;
			break;

		case PAUSE_MULTI:
			// Handle pause menu input, resume or quit options
			if (IsKeyPressed(KEY_SPACE)) currentGameState = GAMEPLAY_MULTI;
			break;

		case PAUSE_CPU:
			// Handle pause menu input, resume or quit options
			if (IsKeyPressed(KEY_SPACE)) currentGameState = GAMEPLAY_CPU;
			break;

		case GAMEOVER:
			// Display game over screen, handle restart or quit options
			if (IsKeyPressed(KEY_M)) currentGameState = MENU;
			break;
		}

		BeginDrawing();

		// Updating
		
		

		
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

		if (currentGameState == GAMEPLAY_MULTI)
		{
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
		}
		
		if (currentGameState == GAMEPLAY_CPU)
		{ 
		// Checking for collision CPU
		if (CheckCollisionCircleRec(Vector2{ ball.x, ball.y }, ball.radius, Rectangle{ cpu.x, cpu.y, cpu.width, cpu.height }))
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


		if (CheckCollisionCircleRec(Vector2{ ballTwo.x, ballTwo.y }, ballTwo.radius, Rectangle{cpu.x, cpu.y, cpu.width, cpu.height }))
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
		}

		ClearBackground(BLACK);

		switch (currentGameState)
		{
		case MENU:

			// Draw the ball moving horizontally with sinus wave
			DrawCircle(sinusBallX, sinusBallY, 15, OrangeRed);

			// Drawing text
			DrawText("-----------------------------------------", GetScreenWidth() / 2 - MeasureText("-----------------------------------------", 60) / 2, GetScreenHeight() / 2 - 360, 60, RED);
			DrawText("-----------------------------------------", GetScreenWidth() / 2 - MeasureText("-----------------------------------------", 60) / 2, GetScreenHeight() / 2 - 350, 60, RED);
			DrawText("BREAK - IN", GetScreenWidth() / 2 - MeasureText("BREAK - IN", 60) / 2, GetScreenHeight() / 2 - 270, 60, PURPLE);
			DrawText("MAIN MENU", GetScreenWidth() / 2 - MeasureText("MAIN MENU", 40) / 2, GetScreenHeight() / 2 - 180, 40, RED);

			DrawText("SINGLE PLAYER: PRESS C", GetScreenWidth() / 2 - MeasureText("SINGLE PLAYER: PRESS C", 30) / 2, GetScreenHeight() / 2 - 110, 30, WHITE);
			DrawText("TWO PLAYER: PRESS ENTER", GetScreenWidth() / 2 - MeasureText("TWO PLAYER: PRESS ENTER", 30) / 2, GetScreenHeight() / 2 - 70, 30, WHITE);
			DrawText("QUIT: PRESS ESCAPE", GetScreenWidth() / 2 - MeasureText("QUIT: PRESS ESCAPE", 30) / 2, GetScreenHeight() / 2 - 30, 30, WHITE);

			//Reseting the game	
			ResetGame();
			break;

		case GAMEPLAY_MULTI:
			// Drawing game elements (player, ball, etc.)
			DrawLine(value.screen_width / 2, 0, value.screen_width / 2, value.screen_height, GRAY);

			//Updating
			player.Update();
			ball.Update(player_score, playerTwo_score, player.x - 20, player.y + player.height / 2);
			playerTwo.Update();
			ballTwo.Update(player_score, playerTwo_score, playerTwo.x + playerTwo.width + 20, playerTwo.y + playerTwo.height / 2);


			//Drawing
			player.Draw();
			playerTwo.Draw();
			ball.Draw();
			ballTwo.Draw();
			blocks.Draw();
	

			//Score text
			DrawText(TextFormat("%i", playerTwo_score), value.screen_width / 4 - 20, 20, 80, WHITE);
			DrawText(TextFormat("%i", player_score), 3 * value.screen_width / 4 - 20, 20, 80, WHITE);
			break;

		case GAMEPLAY_CPU:
			// Drawing game elements (player, ball, etc.)
			DrawLine(value.screen_width / 2, 0, value.screen_width / 2, value.screen_height, GRAY);
			
			//Update
			player.Update();
			ball.Update(player_score, playerTwo_score, player.x - 20, player.y + player.height / 2);
			cpu.Update();
			ballTwo.Update(player_score, playerTwo_score, cpu.x + cpu.width + 20, cpu.y + cpu.height / 2);
			fundrop.Update();

			//Drawing
			player.Draw();
			cpu.Draw();
			ball.Draw();
			ballTwo.Draw();
			blocks.Draw();
			fundrop.Draw();

			//Score text
			DrawText(TextFormat("%i", playerTwo_score), value.screen_width / 4 - 20, 20, 80, WHITE);
			DrawText(TextFormat("%i", player_score), 3 * value.screen_width / 4 - 20, 20, 80, WHITE);
			break;

		case PAUSE_MULTI:
			DrawText("Paused", GetScreenWidth() / 2 - MeasureText("Paused", 20) / 2, GetScreenHeight() / 2, 20, WHITE);
			DrawText("Press SPACE to continue", GetScreenWidth() / 2 - MeasureText("Press SPACE to continue", 20) / 2, GetScreenHeight() / 2 + 30, 20, GRAY);
			break;

		case PAUSE_CPU:
			DrawText("Paused", GetScreenWidth() / 2 - MeasureText("Paused", 20) / 2, GetScreenHeight() / 2, 20, WHITE);
			DrawText("Press SPACE to continue", GetScreenWidth() / 2 - MeasureText("Press SPACE to continue", 20) / 2, GetScreenHeight() / 2 + 30, 20, GRAY);
			break;

		case GAMEOVER:
			DrawText("Game Over! Press M to go to MAIN MENU", GetScreenWidth() / 2 - MeasureText("Game Over! Press M to go to MAIN MENU", 20) / 2, GetScreenHeight() / 2, 20, WHITE);
			break;
		}


		EndDrawing();


	}

	CloseWindow();
	return 0;
}