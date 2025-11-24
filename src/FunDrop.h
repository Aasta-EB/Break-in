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
	SPEED_BALL,
	SPEED_OPPONENT, 
	SPEED_SELF
};


class FunDrop
{ 
public:

	float x = 1400 / 2;
	float y = 900 / 2;
	int speed_x = 6;
	Color drawColor = PURPLE;
	std::vector<Drop> drops;

	FunUpgrade RandomUpgrade();

	void Spawn(int blockX, int blockY, float direction);

	void Draw();

	void Update();
};

