#include "pch.h"
#include "GameObject.h"

GameObject::GameObject()
{
	
}

GameObject::~GameObject()
{
	
}

bool GameObject::Init(Settings* settings)
{
	return false;
}

bool GameObject::Init(int xPosition, int yPosition)
{
	return false;
}

SDL_Rect GameObject::Render()
{
	SDL_Rect rect;

	rect.h = 0;
	rect.w = 0;
	rect.x = 0;
	rect.y = 0;

	return rect;
}

void GameObject::Clean()
{
}

int GameObject::GetWidth()
{
	return width;
}

int GameObject::GetHeight()
{
	return height;
}

float GameObject::GetXPos()
{
	return xPos;
}

float GameObject::GetYPos()
{
	return yPos;
}
