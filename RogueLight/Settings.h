#pragma once

class Settings
{
public:
	Settings();
	~Settings();

	int GetScreenWidth();
	int GetScreenHeight();
	void SetScreenWidth(int screenWidth);
	void SetScreenHeight(int screenHeight);

	int GetScreenRefreshRate();
	float GetMSPerRender();
	void SetScreenRefreshRate(int screenRefreshRate);
	
	int GetUpdatesPerSecond();
	double GetMSPerUpdate();

private:
	int SCREEN_WIDTH, SCREEN_HEIGHT;

	int SCREEN_REFRESH_RATE;
	double MS_PER_REFRESH;

	const int UPDATES_PER_SECOND = 60;
	const double MS_PER_UPDATE = 1000 / UPDATES_PER_SECOND;
};

