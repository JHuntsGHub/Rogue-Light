#include "pch.h"
#include "MapElement.h"


MapElement::MapElement(int xPosition, int yPosition, int type)
{
	width = 128;
	height = width;
	SetMapElementType(type);
	xPos = xPosition;
	yPos = yPosition;
}


MapElement::~MapElement()
{
}

void MapElement::Update()
{
}

SDL_Rect MapElement::Render()
{
	SDL_Rect rect;
	rect.h = height;
	rect.w = width;
	rect.x = xPos;
	rect.y = yPos;
	return rect;
}

void MapElement::SetMapElementType(int type)
{
	mapElementType = type;
}

int MapElement::GetMapElementType()
{
	return mapElementType;
}
