#pragma once
#include <string>
#include <SDL.h>
#include "Settings.h"

using namespace std;

class GameObject
{
public:
	GameObject();
	~GameObject();

	virtual bool Init(Settings* settings);
	virtual bool Init(int xPosition, int yPosition);
	virtual SDL_Rect Render();
	virtual void Clean();

	int GetWidth();
	int GetHeight();

	virtual float GetXPos();
	virtual float GetYPos();


protected:
	float xPos, yPos;
	float width, height;
};

