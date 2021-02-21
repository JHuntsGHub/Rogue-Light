#pragma once
#include "MapElement.h"
#include <list>

class Map
{
public:
	static list<MapElement> GetWalls();
	static list<MapElement> GetFloors();
	//[6][10]

private:
	const int tileLength = 128;
};

