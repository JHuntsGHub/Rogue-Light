#include "pch.h"
#include "Window.h"
#include <iostream>

Window::Window(Settings* settings)
{
	width = settings->GetScreenWidth();
	height = settings->GetScreenHeight();
	score = 0;
	life = 4;
}


Window::~Window()
{
	delete(&width);
	delete(&height);
	SDL_DestroyRenderer(renderer);
	SDL_DestroyWindow(window);
	SDL_Quit();
}

/*
 *	InitialiseWindow() creates the window that the game is ran in.
 *	Most of this was taken from the class tutorials, specifically the "1. Hello World - SDL.pdf" - accessed on 22/10/2019.
 */
bool Window::InitialiseWindow()
{
	if (SDL_Init(SDL_INIT_VIDEO) != 0)
	{
		printf("SDL could not initialise! SDL_Error: %s\n", SDL_GetError());
		return false;
	}

	window = SDL_CreateWindow("Rogue Light", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, width, height, SDL_WINDOW_SHOWN);

	if (window == nullptr)
	{
		printf("Window could not be created! SDL_Error: %s\n", SDL_GetError());
		return false;
	}

	renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);

	if (renderer == nullptr)
	{
		printf("Renderer could not initialise! SDL_Error: %s\n", SDL_GetError());
		return false;
	}
}


/*
*	I used https://www.youtube.com/watch?v=XS3E7Q_5TMg&list=PLEJbjnzD0g7REtyFUestvXSKTyRFs__lu&index=7 to get started with loading images but modified it shortly after.
*/
bool Window::InitialiseImages()
{
	if (IMG_Init(IMG_INIT_PNG) != IMG_INIT_PNG) {
		printf("Failed to initialise Image.\n");
		return false;
	}

	//Loading player's image.
	SDL_Surface* surface = IMG_Load(PLAYER_SPRITE_PATH.c_str());
	if (!surface) {
		printf("Player surface failed.\n");
		return false;
	}
	playerTexture = SDL_CreateTextureFromSurface(renderer, surface);
	if (!playerTexture) {
		printf("Player texture failed.\n");
		return false;
	}

	//Loading enemy's image.
	surface = IMG_Load(ENEMY_SPRITE_PATH.c_str());
	if (!surface) {
		printf("Enemy surface failed.\n");
		return false;
	}
	enemyTexture = SDL_CreateTextureFromSurface(renderer, surface);
	if (!enemyTexture) {
		printf("Enemy texture failed.\n");
		return false;
	}

	//Loading Wall's image.
	surface = IMG_Load(WALL_SPRITE_PATH.c_str());
	if (!surface) {
		printf("Wall surface failed.\n");
		return false;
	}
	wallTexture = SDL_CreateTextureFromSurface(renderer, surface);
	if (!wallTexture) {
		printf("Wall texture failed.\n");
		return false;
	}

	//Loading Floor0's image.
	surface = IMG_Load(FLOOR_0_SPRITE_PATH.c_str());
	if (!surface) {
		printf("Floor0 surface failed.\n");
		return false;
	}
	floor0Texture = SDL_CreateTextureFromSurface(renderer, surface);
	if (!floor0Texture) {
		printf("Floor0 texture failed.\n");
		return false;
	}

	//Loading Floor1's image.
	surface = IMG_Load(FLOOR_1_SPRITE_PATH.c_str());
	if (!surface) {
		printf("Floor1 surface failed.\n");
		return false;
	}
	floor1Texture = SDL_CreateTextureFromSurface(renderer, surface);
	if (!floor1Texture) {
		printf("Floor1 texture failed.\n");
		return false;
	}

	//Loading Bullet Image.
	surface = IMG_Load(BULLET_SPRITE_PATH.c_str());
	if (!surface) {
		printf("Bullet surface failed.\n");
		return false;
	}
	bulletTexture = SDL_CreateTextureFromSurface(renderer, surface);
	if (!bulletTexture) {
		printf("Bullet texture failed.\n");
		return false;
	}

	//Loading Number Images
	for (int i = 0; i < 10; i++)
	{
		surface = IMG_Load(NUM_SPRITES_PATH[i].c_str());
		if (!surface) {
			printf("Number surface failed.\n");
			return false;
		}
		numberTextures[i] = SDL_CreateTextureFromSurface(renderer, surface);
		if (!numberTextures[i]) {
			printf("Number texture failed.\n");
			return false;
		}
	}

	//Loading Heart Image
	surface = IMG_Load(HEART_SPRITE_PATH.c_str());
	if (!surface) {
		printf("Heart surface failed.\n");
		return false;
	}
	heartTexture = SDL_CreateTextureFromSurface(renderer, surface);
	if (!heartTexture) {
		printf("Heart texture failed.\n");
		return false;
	}

	//Loading Hash Image
	surface = IMG_Load(HASH_SPRITE_PATH.c_str());
	if (!surface) {
		printf("Hash surface failed.\n");
		return false;
	}
	hashTexture = SDL_CreateTextureFromSurface(renderer, surface);
	if (!hashTexture) {
		printf("Hash texture failed.\n");
		return false;
	}

	

	SDL_FreeSurface(surface);
	return true;
}


void Window::ClearRenderer()
{
	SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
	SDL_RenderClear(renderer);
}

void Window::DrawToScreen()
{
	DisplayScoreAndLife();
	SDL_RenderPresent(renderer);
}

void Window::UpdateLife(int num)
{
	life = num;
}

void Window::AddScore(int num)
{
	score += num;
}

void Window::DisplayScoreAndLife()
{
	int xPos = 45, yPos = 45;

	SDL_Rect rect;
	rect.h = 32;
	rect.w = 32;

	//hash first
	rect.x = xPos;
	rect.y = yPos;
	AddToRenderer(rect, hash);

	//then the score
	rect.x += xPos + 5;
	AddToRenderer(rect, num);

	//then the heart
	rect.x += xPos * 2;
	AddToRenderer(rect, heart);

	//then draw life bar
	rect.x += xPos + 5;
	if (life < 0)
		life = 0;
	rect.w = life * 45;

	SDL_SetRenderDrawColor(renderer, 147, 13, 49, 255);
	SDL_RenderFillRect(renderer, &rect);
}



void Window::AddToRenderer(SDL_Rect rect, int renderType)
{

	switch (renderType)
	{
		case(Player):
			SDL_RenderCopy(renderer, playerTexture, nullptr, &rect);
			break;
		case(enemy):
			SDL_RenderCopy(renderer, enemyTexture, nullptr, &rect);
			break;
		case(floor0):
			SDL_RenderCopy(renderer, floor0Texture, nullptr, &rect);
			break;
		case(floor1):
			SDL_RenderCopy(renderer, floor1Texture, nullptr, &rect);
			break;
		case(wall):
			SDL_RenderCopy(renderer, wallTexture, nullptr, &rect);
			break;
		case(bullet):
			SDL_RenderCopy(renderer, bulletTexture, nullptr, &rect);
			break;
		case(heart):
			SDL_RenderCopy(renderer, heartTexture, nullptr, &rect);
			break;
		case(num):
			SDL_RenderCopy(renderer, numberTextures[score], nullptr, &rect);
			break;
		case(hash):
			SDL_RenderCopy(renderer, hashTexture, nullptr, &rect);
			break;
		default:
			SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
			SDL_RenderFillRect(renderer, &rect);
			break;
	}
}