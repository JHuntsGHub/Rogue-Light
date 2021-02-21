#include "pch.h"
#include "Bullet.h"
#include <iostream>

Bullet::Bullet(int xPosition, int yPosition, int direction)
{
	speed = 10;
	DetermineDirection(direction);

	xPos = xPosition;
	yPos = yPosition;
	height = 27;
	width = height;

}


Bullet::~Bullet()
{
}

void Bullet::Update()
{
	xPos += xChange;
	yPos += yChange;
}

SDL_Rect Bullet::Render()
{
	SDL_Rect rect;

	rect.h = height;
	rect.w = width;
	rect.x = xPos;
	rect.y = yPos;

	return rect;
}

void Bullet::DetermineDirection(int direction)
{
	enum bulletDirection {Left, Right, Up, Down};

	switch (direction)
	{
		case Left:
			xChange = -speed;
			yChange = 0;
			break;

		case Right:
			xChange = speed;
			yChange = 0;
			break;

		case Up:
			xChange = 0;
			yChange = -speed;
			break;

		case Down:
			xChange = 0;
			yChange = speed;
			break;
	}
}

void Bullet::Clean()
{
}

float Bullet::GetXPos()
{
	return xPos + width / 2;
}

float Bullet::GetYPos()
{
	return yPos + width / 2;
}
