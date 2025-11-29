#include "FunDrop.h"

FunUpgrade FunDrop::RandomUpgrade()
{
	FunUpgrade upgrade_choices[] = { ENLARGE_BALL, ENLARGE_PADDLE, SPEED_BALL, SPEED_OPPONENT, SPEED_SELF };
	return upgrade_choices[GetRandomValue(1, 4)];
}

void FunDrop::Spawn(int blockX, int blockY, float direction)
{
	int dropOrNot = GetRandomValue(1, 100);
	if (dropOrNot <= 50)
	{
		Drop drop = { { blockX, blockY }, direction * speed_x, true };
		drops.push_back(drop);
	}
}

void FunDrop::Draw()
{
	for (Drop drop : drops)
	{
		if (drop.active)
		{
			DrawPoly(drop.position, 6, 25, drop.rotation, drawColor);
		}
	}

}

void FunDrop::Update()
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

void FunDrop::Reset()
{
	drops.clear();
}
