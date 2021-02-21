#pragma once
#include "GameObject.h"

class Bullet : public GameObject
{
public:
	Bullet(int xPosition, int yPosition, int direction);
	~Bullet();

	void Update();
	SDL_Rect Render() override;
	void DetermineDirection(int direction);
	virtual void Clean();

	float GetXPos() override;
	float GetYPos() override;

private:
	float speed;
	float xChange, yChange;
};

