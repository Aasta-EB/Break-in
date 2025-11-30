#pragma once
#include "Paddle_1.h"
#include "Paddle_2.h"
#include "Paddle_CPU.h"
#include "Ball.h"
#include "Blocks.h"
#include "FunDrop.h"

#include <raylib.h>
#include <iostream>



//Game state
enum GameState
{
	MENU, //single player or multiplayer
	GAMEPLAY_MULTI,
	GAMEPLAY_CPU,
	PAUSE_MULTI, //space to pause
	PAUSE_CPU,
	GAMEOVER //go from gameover to menu
};

GameState currentGameState = MENU;

extern Paddle_1 player;
extern Paddle_2 playerTwo;
extern Paddle_CPU cpu;
extern FunDrop fundrop;
extern Ball ball;
extern Ball ballTwo;
extern Blocks blocks;


int screen_width = 1400;
int screen_height = 900;

//Color
Color CornflowerBlue{ 100, 143, 255, 255 };
Color OrangeRed{ 254, 97, 0, 255 };


// Sinus-wave movement variables for Main-Menu
float sinusBallX = 0.0f;
float sinusBallY = screen_height / 2;
float amplitude = 100.0f;
float frequency = 1.0f;
float speed = 2.0f;
float sinusTime = 0.0f;

class Window
{
public:

//variables
int player_score = 6;
int playerTwo_score = 6;

// Resetting the game
void ResetGame()
{
	player_score = 6;
	playerTwo_score = 6;
	ball.ResetBall(player.x - 50, player.y);
	ballTwo.ResetBall(playerTwo.x + 50, playerTwo.y);
	player.ResetPaddle();
	playerTwo.ResetPaddleTwo();
	cpu.ResetPaddleCPU();
	blocks.initialize();
	fundrop.Reset();
}

void CheckGameState()
{
	switch (currentGameState)
	{
	case MENU:
		// Handle menu input
		if (IsKeyPressed(KEY_ENTER)) currentGameState = GAMEPLAY_MULTI;
		if (IsKeyPressed(KEY_C)) currentGameState = GAMEPLAY_CPU;

		sinusTime += GetFrameTime();
		sinusBallX += speed;

		// If the Sinus ball moves off the screen to the right, reseting its position to the left
		if (sinusBallX > screen_width + 20)
			sinusBallX = -20;

		// Update y position of the ball
		sinusBallY = (screen_height / 2) + amplitude * sinf(frequency * sinusTime);
		break;

	case GAMEPLAY_MULTI:
		// Handle player input
		if (IsKeyPressed(KEY_SPACE)) currentGameState = PAUSE_MULTI;
		if (IsKeyPressed(KEY_M)) currentGameState = MENU;
		break;

	case GAMEPLAY_CPU:
		// Handle player input
		if (IsKeyPressed(KEY_SPACE)) currentGameState = PAUSE_CPU;
		if (IsKeyPressed(KEY_M)) currentGameState = MENU;
		if (player_score == 0 or playerTwo_score == 0)
		{
			currentGameState = GAMEOVER;
		}
		break;

	case PAUSE_MULTI:
		// Handle pause menu input
		if (IsKeyPressed(KEY_SPACE)) currentGameState = GAMEPLAY_MULTI;
		if (player_score == 0 or playerTwo_score == 0)
		{
			currentGameState = GAMEOVER;
		}
		break;

	case PAUSE_CPU:
		// Handle pause menu input
		if (IsKeyPressed(KEY_SPACE)) currentGameState = GAMEPLAY_CPU;
		break;

	case GAMEOVER:
		// Display gameover screen, sends player to Main Menu
		if (IsKeyPressed(KEY_M)) currentGameState = MENU;
		break;
	}
}

void HandleGameStates()
{

	switch (currentGameState)
	{
	case MENU:

		// Draw the ball with sinus wave
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
		DrawLine(screen_width / 2, 0, screen_width / 2, screen_height, GRAY);

		//Updating
		player.Update();
		ball.Update(player_score, playerTwo_score, player.x - 20, player.y + player.height / 2);
		playerTwo.Update();
		ballTwo.Update(player_score, playerTwo_score, playerTwo.x + playerTwo.width + 20, playerTwo.y + playerTwo.height / 2);
		fundrop.Update();
		CheckFundropCollision();


		//Drawing
		player.Draw();
		playerTwo.Draw();
		ball.Draw();
		ballTwo.Draw();
		blocks.Draw();
		fundrop.Draw();


		//Score text
		DrawText(TextFormat("%i", playerTwo_score), screen_width / 4 - 20, 20, 80, WHITE);
		DrawText(TextFormat("%i", player_score), 3 * screen_width / 4 - 20, 20, 80, WHITE);
		break;

	case GAMEPLAY_CPU:
		DrawLine(screen_width / 2, 0, screen_width / 2, screen_height, GRAY);

		//Update
		player.Update();
		ball.Update(player_score, playerTwo_score, player.x - 20, player.y + player.height / 2);
		cpu.Update();
		ballTwo.Update(player_score, playerTwo_score, cpu.x + cpu.width + 20, cpu.y + cpu.height / 2);
		fundrop.Update();
		CheckFundropCollision();

		//Drawing
		player.Draw();
		cpu.Draw();
		ball.Draw();
		ballTwo.Draw();
		blocks.Draw();
		fundrop.Draw();

		//Score text
		DrawText(TextFormat("%i", playerTwo_score), screen_width / 4 - 20, 20, 80, WHITE);
		DrawText(TextFormat("%i", player_score), 3 * screen_width / 4 - 20, 20, 80, WHITE);
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


}





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

void CheckPaddleCollision()
{
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


		if (CheckCollisionCircleRec(Vector2{ ballTwo.x, ballTwo.y }, ballTwo.radius, Rectangle{ cpu.x, cpu.y, cpu.width, cpu.height }))
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

}



};

