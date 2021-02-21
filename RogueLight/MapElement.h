#pragma once
#include "GameObject.h"
class MapElement : public GameObject
{
public:
	MapElement(int xPosition, int yPosition, int type);
	~MapElement();


	void Update();
	SDL_Rect Render() override;

	void SetMapElementType(int type);
	int GetMapElementType();

private:
	int mapElementType;
};

