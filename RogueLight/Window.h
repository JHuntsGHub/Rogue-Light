#pragma once
#include "Settings.h"
#include <SDL.h>
#include <SDL_image.h>
#include <string>

class Window
{
public:
	Window(Settings* settings);
	~Window();

	bool InitialiseWindow();
	bool InitialiseImages();
	void ClearRenderer();
	void AddToRenderer(SDL_Rect rect, int renderType);
	void DrawToScreen();

	void UpdateLife(int num);
	void AddScore(int num);

private:
	int width, height;
	int score, life;
	const int numberOffset = 32;

	enum renderType { Player, enemy, floor0, floor1, wall, bullet, heart, num , hash};

	void DisplayScoreAndLife();
	
	SDL_Window* window = nullptr;
	SDL_Renderer* renderer = NULL;

	SDL_Texture *playerTexture = nullptr,
				*enemyTexture = nullptr,
				*wallTexture = nullptr,
				*floor0Texture = nullptr,
				*floor1Texture = nullptr,
				*bulletTexture = nullptr,
				*heartTexture = nullptr,
				*hashTexture = nullptr;
	SDL_Texture *numberTextures[10];

	const std::string PLAYER_SPRITE_PATH = "Assets/Textures/Player.png";
	const std::string ENEMY_SPRITE_PATH = "Assets/Textures/Zombie.png";
	const std::string WALL_SPRITE_PATH = "Assets/Textures/Wall.png";
	const std::string FLOOR_0_SPRITE_PATH = "Assets/Textures/Floor0.png";
	const std::string FLOOR_1_SPRITE_PATH = "Assets/Textures/Floor1.png";
	const std::string BULLET_SPRITE_PATH = "Assets/Textures/Bullet.png";
	const std::string HEART_SPRITE_PATH = "Assets/Textures/Heart.png";
	const std::string HASH_SPRITE_PATH = "Assets/Textures/Hash.png";

	const std::string NUM_SPRITES_PATH[10] = { "Assets/Textures/Number_0.png",
												"Assets/Textures/Number_1.png",
												"Assets/Textures/Number_2.png",
												"Assets/Textures/Number_3.png",
												"Assets/Textures/Number_4.png",
												"Assets/Textures/Number_5.png",
												"Assets/Textures/Number_6.png",
												"Assets/Textures/Number_7.png",
												"Assets/Textures/Number_8.png",
												"Assets/Textures/Number_9.png"};
};

