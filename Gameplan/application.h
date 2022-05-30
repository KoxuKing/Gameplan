#pragma once
#include "Game.h"
#include "UI.h"
#include <SFML/Window.hpp>

class Application
{
public:
	int run();
	int shutdown();
	
	struct Mouse
	{
		int x;
		int y;
		bool clicked_left = false;
		bool clicked_right = false;
	};
	Mouse mouse;

	enum ApplicationState
	{
		STATE_UI = 0,
		STATE_GAME = 1
	};

	int State = ApplicationState::STATE_UI;
	Game game;
private:

	void updateUserInputs(sf::Event _event);
	void createWindow();

	UI ui;
	sf::Window window;

	int window_width = 800;
	int window_height = 600;
	int fps = 60;
};