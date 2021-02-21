#pragma once
#include "Entity.h"
#include <SDL.h>

class Player : public Entity
{
public:
	Player();
	~Player();

	int GetScore();
	float GetXPos();
	float GetYPos();
	void SetXPos(float x);
	void SetYPos(float y);

	enum userInputEnum { movingLeft, movingRight, movingUp, movingDown, firingLeft, firingRight, firingUp, firingDown };

	bool Init(Settings* settings) override;
	void Update(bool userInput[8]);
	SDL_Rect Render() override;
	void Clean() override;

private:
	float speed;

	void DoPlayerMovement(bool userInput[8]);

	SDL_Rect rect;
};

