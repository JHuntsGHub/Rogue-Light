// RogueLight.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include "pch.h"
#include "Settings.h"
#include "Player.h"
#include "Enemy.h"
#include "MapElement.h"
#include "Time.h"
#include "Window.h"
#include "Map.h"
#include "Bullet.h"
#include <iostream>
#include <list>
#include <SDL.h>
#include <stdio.h>

using namespace std;

const string ENEMY1_SPRITE_PATH = "Assets\\CharactersSpriteSheet.bmp";
const string MAP_ELEMENTS_SPRITE_PATH = "Assets\\TerrainSpriteSheet.bmp";

Time* timer = new Time();
Settings* settings = new Settings();
enum typesOfEnemies { stationary = 0, standard = 1, fast = 2 };

bool isGameRunning = true;

SDL_Event event;
enum userInputEnum { movingLeft, movingRight, movingUp, movingDown, firingLeft, firingRight, firingUp, firingDown };
bool userInputArray[8] = { false, false, false, false, false, false, false, false };

Window* wind = new Window(settings);
SDL_Surface* frameToRender = NULL;

SDL_Surface* enemyImage = NULL;

Player* player = new Player();

float bulletCooldown = 0, bulletCooldownLength = 1.5;
list<Bullet> bullets;

int life = 4;
float hitCooldown = 0, hitCooldownLength = 1.5;

Enemy enemies[5] = {};

Map map;
list<MapElement> walls;
list<MapElement> floors;


void Shutdown()
{
	/*delete &ENEMY1_SPRITE_PATH;
	delete &MAP_ELEMENTS_SPRITE_PATH;

	delete &isGameRunning;

	delete &event;

	delete renderer;
	delete wind;
	delete frameToRender;

	delete enemyImage;

	delete timer;
	delete settings;

	delete player;
	delete &enemies;
	delete &mapElements;*/
}

/*
*	This method will check if all condidtions are good to continue running the game.
*	If the game needs to shut down all the necessary methods will be called here.
*/
bool UpdateLifecycle()
{
	if (isGameRunning)
		return true;
	else {
		Shutdown();
		return false;
	}
}

/*
	GetUserInput() was greatly helped by https://www.libsdl.org/release/SDL-1.2.15/docs/html/guideinputkeyboard.html
	The methodology of using a userInputArray is mine but the structure of the switch is theirs.
*/
void GetUserInput()
{
	while (SDL_PollEvent(&event))
	{
		switch (event.type) {

			case SDL_KEYDOWN:
				switch(event.key.keysym.sym)
				{
					case SDLK_a:
						userInputArray[userInputEnum(movingLeft)] = true;
						break;
					case SDLK_d:
						userInputArray[userInputEnum(movingRight)] = true;
						break;
					case SDLK_w:
						userInputArray[userInputEnum(movingUp)] = true;
						break;
					case SDLK_s:
						userInputArray[userInputEnum(movingDown)] = true;
						break;
					case SDLK_LEFT:
						userInputArray[userInputEnum(firingLeft)] = true;
						break;
					case SDLK_RIGHT:
						userInputArray[userInputEnum(firingRight)] = true;
						break;
					case SDLK_UP:
						userInputArray[userInputEnum(firingUp)] = true;
						break;
					case SDLK_DOWN:
						userInputArray[userInputEnum(firingDown)] = true;
						break;
					default:
						break;
				}
				break;

			case SDL_KEYUP:
				switch (event.key.keysym.sym)
				{
					case SDLK_a:
						userInputArray[userInputEnum(movingLeft)] = false;
						break;
					case SDLK_d:
						userInputArray[userInputEnum(movingRight)] = false;
						break;
					case SDLK_w:
						userInputArray[userInputEnum(movingUp)] = false;
						break;
					case SDLK_s:
						userInputArray[userInputEnum(movingDown)] = false;
						break;
					case SDLK_LEFT:
						userInputArray[userInputEnum(firingLeft)] = false;
						break;
					case SDLK_RIGHT:
						userInputArray[userInputEnum(firingRight)] = false;
						break;
					case SDLK_UP:
						userInputArray[userInputEnum(firingUp)] = false;
						break;
					case SDLK_DOWN:
						userInputArray[userInputEnum(firingDown)] = false;
						break;
					default:
						break;
					}
				break;

			case SDL_QUIT:
				isGameRunning = false;
				break;

			default:
				break;
		}
	}
}

//int i = 0, j = 0;//delete this line.
void UpdateAll()
{
	//std::cerr << "U:" << ++i << "\n";//delete this line.
	//Updating the map elements
	/*for (MapElement me : mapElements)
		me.Update();*/

	//Updating the enemies
	for (Enemy en : enemies)
		en.Update();

	//Updateing the bullets
	list<Bullet>::iterator iter;
	for (iter = bullets.begin(); iter != bullets.end(); iter++)
		iter->Update();

	//Updating the player
	player->Update(userInputArray);
}

void RenderAll()
{
	enum renderType { Player, enemy, floor0, floor1, wall, bullet };
	//std::cerr << "R:" << ++j << "\n";//delete this line.

	wind->ClearRenderer();

	//Rendering the walls
	for (MapElement w : walls)
		wind->AddToRenderer(w.Render(), renderType(wall));

	//Rendering the floors
	for (MapElement f : floors)
		wind->AddToRenderer(f.Render(), f.GetMapElementType());

	//Rendering the enemies
	for (Enemy en : enemies)
		if(!en.isDefeated)
			wind->AddToRenderer(en.Render(), renderType(enemy));

	//Rendering the bullets
	for (Bullet b : bullets)
		wind->AddToRenderer(b.Render(), renderType(bullet));

	//Rendering the player
	wind->AddToRenderer(player->Render(), renderType(Player));

	//My game loop should have taken care of this.
	//SDL_Delay(16);

	wind->DrawToScreen();
}

bool WithinRange(float i, float min, float max)
{
	if (min < i && i < max)
		return true;
	return false;
}

void PlayerHitEnemy()
{
	if (hitCooldown <= 0)
	{
		hitCooldown = hitCooldownLength;
		printf("player hit enemy\n");
		life -= 1;
		wind->UpdateLife(life);
		if (life <= 0) {

		}
		cout << life << "\n";
	}
}

void BulletHitEnemy(int enemyIndex)
{
	enemies[enemyIndex].isDefeated = true;

	wind->AddScore(1);
}

void ResolveCollisions()
{
	hitCooldown -= 0.05;

	float playerLeft = player->GetXPos();
	float playerTop = player->GetYPos();

	float playerRight = player->GetXPos() + player->GetWidth();
	float playerBottom = player->GetYPos() + player->GetHeight();

	float entityLeft, entityRight, entityTop, entityBottom;

	//list<MapElement>::iterator iter;
	//for (iter = walls.begin(); iter != walls.end(); iter++)
	//{
	//	entityLeft = iter->GetXPos();
	//	entityRight = iter->GetXPos() + iter->GetWidth();
	//	entityTop = iter->GetYPos();
	//	entityBottom = iter->GetYPos() + iter->GetHeight();

	//	/*if (WithinRange(playerLeft, entityLeft, entityRight) && WithinRange(playerTop, entityTop, entityBottom))
	//	{
	//		if (WithinRange(playerRight, entityTop, entityBottom) && !WithinRange(playerRight, entityLeft, entityRight))
	//		{
	//			player->SetXPos(entityRight);
	//		}
	//		if (WithinRange(playerBottom, entityLeft, entityRight) && !WithinRange(playerBottom, entityTop, entityBottom))
	//		{
	//			player->SetYPos(entityBottom);
	//		}
	//	}*/
	//	/*if (playerTop < entityBottom && playerBottom > entityBottom && !WithinRange(playerLeft, entityLeft, entityRight) && !WithinRange(playerBottom, entityTop, entityBottom))
	//		player->SetYPos(entityBottom);*/
	//	//if(WithinRange(playerTop, entity))
	//}

	//Handles collisions with walls.
	if (playerLeft < 128)
		player->SetXPos(128);
	if (playerRight > settings->GetScreenWidth() - 128)
		player->SetXPos(settings->GetScreenWidth() - 128 - player->GetWidth());
	if (playerTop < 128)
		player->SetYPos(128);
	if (playerBottom > settings->GetScreenHeight() - 128)
		player->SetYPos(settings->GetScreenHeight() - 128 - player->GetHeight());


	//Looking for collisions between player and enemies.
	for (int i = 0; i < 5; i++)
	{
		if (!enemies[i].isDefeated)
		{
			entityLeft = enemies[i].GetXPos();
			entityRight = enemies[i].GetXPos() + enemies[i].GetWidth();
			entityTop = enemies[i].GetYPos();
			entityBottom = enemies[i].GetYPos() + enemies[i].GetHeight();

			if (WithinRange(playerLeft, entityLeft, entityRight)) {

				if (WithinRange(playerTop, entityTop, entityBottom) || WithinRange(playerBottom, entityTop, entityBottom))
					PlayerHitEnemy();
			}
			else if (WithinRange(playerRight, entityLeft, entityRight)) {
				if (WithinRange(playerTop, entityTop, entityBottom) || WithinRange(playerBottom, entityTop, entityBottom))
					PlayerHitEnemy();
			}
		}
	}

	//Looks for bullet collisions.
	float bulletRadius = 27 / 2;
	list<Bullet>::iterator bull;
	for (bull = bullets.begin(); bull != bullets.end(); bull++)
	{
		//Looks for collisions with enemies first.
		for (int i = 0; i < 5; i++)
		{
			if (!enemies[i].isDefeated)
			{
				entityLeft = enemies[i].GetXPos();
				entityRight = enemies[i].GetXPos() + enemies[i].GetWidth();
				entityTop = enemies[i].GetYPos();
				entityBottom = enemies[i].GetYPos() + enemies[i].GetHeight();

				if (WithinRange(bull->GetXPos() - bulletRadius, entityLeft, entityRight)) {

					if (WithinRange(bull->GetYPos() - bulletRadius, entityTop, entityBottom) || WithinRange(bull->GetYPos() + bulletRadius, entityTop, entityBottom))
					{
						BulletHitEnemy(i);
						bullets.erase(bull);
					}
				}
				else if (WithinRange(bull->GetXPos() + bulletRadius, entityLeft, entityRight)) {
					if (WithinRange(bull->GetYPos() - bulletRadius, entityTop, entityBottom) || WithinRange(bull->GetYPos() + bulletRadius, entityTop, entityBottom))
					{
						BulletHitEnemy(i);
						bullets.erase(bull);
					}
				}
			}
		}

		//Looks for collisions with walls.
		if (bull->GetXPos() - bulletRadius < 128 || bull->GetXPos() + bulletRadius > settings->GetScreenWidth() - 128 ||
			bull->GetYPos() - bulletRadius < 128 || bull->GetYPos() + bulletRadius > settings->GetScreenHeight() - 128)
		{
			bullets.erase(bull);
		}
	}

}

enum bulletDirection { Left, Right, Up, Down };

void ShootBullet(int direction)
{
	bulletCooldown = bulletCooldownLength;

	switch (direction)
	{
		case bulletDirection(Left):
			bullets.push_back(Bullet(player->GetXPos() - 20, player->GetYPos() + player->GetHeight() / 2, bulletDirection(Left)));
			break;
		case bulletDirection(Right):
			bullets.push_back(Bullet(player->GetXPos() + player->GetWidth() + 15, player->GetYPos() + player->GetHeight() / 2, bulletDirection(Right)));
			break;
		case bulletDirection(Up):
			bullets.push_back(Bullet(player->GetXPos() + player->GetWidth() / 2, player->GetYPos() - 5, bulletDirection(Up)));
			break;
		case bulletDirection(Down):
			bullets.push_back(Bullet(player->GetXPos() + player->GetWidth() / 2, player->GetYPos() + player->GetHeight() + 5, bulletDirection(Down)));
			break;
	}
}

void DoPlayerShooting()
{

	bulletCooldown -= 0.05;
	if (bulletCooldown <= 0)
	{
		int direction = -1;

		if (userInputArray[userInputEnum(firingLeft)] && !userInputArray[userInputEnum(firingRight)] && !userInputArray[userInputEnum(firingUp)] && !userInputArray[userInputEnum(firingDown)])
			direction = bulletDirection(Left);
		else if (!userInputArray[userInputEnum(firingLeft)] && userInputArray[userInputEnum(firingRight)] && !userInputArray[userInputEnum(firingUp)] && !userInputArray[userInputEnum(firingDown)])
			direction = bulletDirection(Right);
		else if (!userInputArray[userInputEnum(firingLeft)] && !userInputArray[userInputEnum(firingRight)] && userInputArray[userInputEnum(firingUp)] && !userInputArray[userInputEnum(firingDown)])
			direction = bulletDirection(Up);
		else if (!userInputArray[userInputEnum(firingLeft)] && !userInputArray[userInputEnum(firingRight)] && !userInputArray[userInputEnum(firingUp)] && userInputArray[userInputEnum(firingDown)])
			direction = bulletDirection(Down);

		if (direction != -1)
			ShootBullet(direction);
	}
}

void CleanAll()
{
	player->Clean();
	if (player) {
		delete player;
		player = nullptr;
	}
}

//The Game loop was heavily inspired by one found in "Game Programming Patterns" by Robert Nystrom (page 131).
void GameLoop()
{
	do
	{
		GetUserInput();
		UpdateAll();
		DoPlayerShooting();
		ResolveCollisions();
		RenderAll();
		SDL_Delay(16);

	} while (UpdateLifecycle());
}

bool InitialiseObjects()
{

	//Load entities here:
	if (!player->Init(settings))
	{
		printf("Player object failed to load.");
		return false;
	}

	int spawnPoints[5][2] = { {150,150},{400,200},{800,500},{950,250},{250,450} };
	for (int i = 0; i < 5; i++)
	{
		enemies[i] = Enemy::Enemy();
		
		if (!enemies[i].Init(spawnPoints[i][0], spawnPoints[i][1]))
		{
			printf("Enemy failed to initialise.");
			return false;
		}
	}

	floors = Map::GetFloors();
	walls = Map::GetWalls();


	return true;
}


///The main just sets up the window and then starts the game loop. In future, I may choose to load assets here first.
int main(int argc, char* argv[])
{
	if (!wind->InitialiseWindow())
	{
		printf("ERROR: Window failed to initialise! Closing program...");
		return 1;
	}

	if (!InitialiseObjects())
	{
		printf("ERROR: Objects failed to initialise! Closing program...");
		return 1;
	}

	if (!wind->InitialiseImages())
	{
		printf("ERROR: Images failed to initialise! Closing program...");
		return 1;
	}

	GameLoop();
	return 0;
}