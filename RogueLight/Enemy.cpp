#include "pch.h"
#include "Enemy.h"


Enemy::Enemy()
{
}


Enemy::~Enemy()
{
}

bool Enemy::Init(int xPosition, int yPosition)
{
	width = 79;
	height = 101;
	xPos = xPosition;
	yPos = yPosition;
	isDefeated = false;
	return true;
}



int Enemy::GetEnemyType()
{
	return enemyType;
}

void Enemy::DoBehavior(int enemyType)
{
	
}

void Enemy::Update()
{
}

SDL_Rect Enemy::Render()
{
	SDL_Rect rect;
	rect.h = height;
	rect.w = width;
	rect.x = xPos;
	rect.y = yPos;
	return rect;
}
