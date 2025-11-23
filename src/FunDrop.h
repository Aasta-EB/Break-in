#pragma once
#include <algorithm>
#include <raylib.h>
#include <iostream>
#include <vector>
#include <string>

typedef struct Drop {
	Vector2 position;
	int speed;
	float rotation;
	bool active = true;
} Drop;

enum FunUpgrade
{
	ENLARGE_BALL, 
	ENLARGE_PADDLE,
	//SPEED_BALL,
	//SPEED_OPPONENT, 
	//SPEED_SELF,
	//MANIPULATE_MOVEMENT
};


class FunDrop
{ 
public:

	float x = 1400 / 2;
	float y = 900 / 2;
	int speed_x = 6;
	Color drawColor = PURPLE;
	std::vector<Drop> drops;

	FunUpgrade RandomUpgrade()
	{
		FunUpgrade upgrade_choices[] = {ENLARGE_BALL, ENLARGE_PADDLE};
		return upgrade_choices[GetRandomValue(0, 1)] ;
	}

	void Spawn(int blockX, int blockY, float direction)
	{
		int dropOrNot = GetRandomValue(1,100);
		if (dropOrNot <= 50)
		{
			Drop drop = { {blockX, blockY}, direction * speed_x, true };
			drops.push_back(drop);
		}
	}

	void Draw()
	{
		for (Drop drop : drops)
		{
			if (drop.active)
			{
			DrawPoly(drop.position, 6, 25, drop.rotation, drawColor);
			}
		}

	}

	void Update()
	{
		for (Drop& drop : drops)
		{
			if (drop.active)
			{
				drop.position.x += drop.speed;
				drop.rotation += 0.7f;
			}
		}
	}
};

