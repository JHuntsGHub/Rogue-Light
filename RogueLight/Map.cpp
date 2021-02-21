#include "pch.h"
#include "Map.h"

//[10][6]
enum Type { floor0 = 2, floor1, wall };

list<MapElement> Map::GetWalls()
{
	list<MapElement> walls;

	//adds top and bottom rows of the grid.
	for (int i = 0; i < 10; i++)
	{
		walls.push_back(MapElement::MapElement(i * 128, 0, wall));
		walls.push_back(MapElement::MapElement(i * 128, 5 * 128, wall));
	}

	//adds the sides of the grid.
	for (int i = 1; i < 6; i++)
	{
		walls.push_back(MapElement::MapElement(0, i * 128, wall));
		walls.push_back(MapElement::MapElement(9 * 128, i * 128, wall));
	}

	return walls;
}

list<MapElement> Map::GetFloors()
{
	list<MapElement> floors;

	//adds the floors
	for (int i = 1; i < 9; i++)
	{
		for (int j = 1; j < 5; j++)
		{
			floors.push_back(MapElement::MapElement(i * 128, j * 128, ((i*j) % 2) + 2));
		}
	}

	return floors;
}
