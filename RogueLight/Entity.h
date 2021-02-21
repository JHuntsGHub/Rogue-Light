#pragma once
#include "GameObject.h"

class Entity : public GameObject
{
public:
	Entity();
	~Entity();
	string GetEntityName();
	float GetEntityHP();

private:
	string name;
	float HP;
};

