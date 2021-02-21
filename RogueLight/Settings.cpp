#include "pch.h"
#include "Settings.h"


Settings::Settings()
{
	SCREEN_HEIGHT = 768;
	SCREEN_WIDTH = 1280;
	SCREEN_REFRESH_RATE = 60;
	SetScreenRefreshRate(SCREEN_REFRESH_RATE);
}


Settings::~Settings()
{
}

int Settings::GetScreenWidth() { return SCREEN_WIDTH; }
int Settings::GetScreenHeight() { return SCREEN_HEIGHT; }

int Settings::GetScreenRefreshRate() { return SCREEN_REFRESH_RATE; }
float Settings::GetMSPerRender() { return MS_PER_REFRESH; }

int Settings::GetUpdatesPerSecond() { return UPDATES_PER_SECOND; }
double Settings::GetMSPerUpdate() { return MS_PER_UPDATE; }

void Settings::SetScreenWidth(int screenWidth) { SCREEN_WIDTH = screenWidth; }
void Settings::SetScreenHeight(int screenHeight) { SCREEN_HEIGHT = screenHeight; }

void Settings::SetScreenRefreshRate(int screenRefreshRate)
{
	SCREEN_REFRESH_RATE = screenRefreshRate;
	MS_PER_REFRESH = 1000 / SCREEN_REFRESH_RATE;
}