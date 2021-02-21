#pragma once
#include "Entity.h"
class Enemy : public Entity
{
public:
	Enemy();
	~Enemy();
	bool Init(int xPosition, int yPosition) override;
	int GetEnemyType();
	void DoBehavior(int enemyType);

	void Update();
	SDL_Rect Render() override;

	bool isDefeated;

private:
	int enemyType;
	float moveSpeed;
	
};

