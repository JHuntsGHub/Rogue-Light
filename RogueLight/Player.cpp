#include "pch.h"
#include "Player.h"


Player::Player()
{
	/*this->renderer = renderer;
	playerSurface = NULL;*/
}


Player::~Player()
{

}

int Player::GetScore()
{
	return 0;
}

float Player::GetXPos()
{
	return xPos;
}

float Player::GetYPos()
{
	return yPos;
}

void Player::SetXPos(float x)
{
	xPos = x;
}

void Player::SetYPos(float y)
{
	Player::yPos = y;
}

bool Player::Init(Settings* settings)
{
	speed = 5.5;

	width = 70;
	height = 96;
	xPos = settings->GetScreenWidth() / 2 - width / 2;
	yPos = settings->GetScreenHeight() / 2 - height / 2;

	return true;
}

void Player::Update(bool userInput[8])
{
	DoPlayerMovement(userInput);
}

void Player::DoPlayerMovement(bool userInput[8])
{
	int xDiff = 0, yDiff = 0;

	if (userInput[userInputEnum(movingLeft)])
		xDiff -= speed;
	if (userInput[userInputEnum(movingRight)])
		xDiff += speed;
	if (userInput[userInputEnum(movingUp)])
		yDiff -= speed;
	if (userInput[userInputEnum(movingDown)])
		yDiff += speed;
	
	xPos += xDiff;
	yPos += yDiff;
}

SDL_Rect Player::Render()
{
	rect.w = width;
	rect.h = height;
	
	rect.x = xPos;
	rect.y = yPos;

	return rect;
}

void Player::Clean()
{
	//SDL_DestroyTexture(texture);
}
