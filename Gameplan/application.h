#pragma once
#include "Game.h"
#include <SFML/Graphics.hpp>
#include "UI.h"

class Application
{
public:
	Application();
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
	sf::RenderWindow window;

	int window_width = 800;
	int window_height = 600;
private:

	void updateUserInputs(sf::Event _event);
	void createWindow();

	UI ui = UI(this);
	int fps = 60;
};