#pragma once
#include "Game.h"
#include "UI.h"

class application
{
public:
	int run();
	int shutdown();
	
	struct MousePos
	{
		int x;
		int y;
	};
	MousePos MousePosition;

	enum ApplicationState
	{
		STATE_UI = 0,
		STATE_GAME = 1
	};

	int State;
	Game game;
private:

	void updateUserInputs();
	UI ui;
	//window size
};