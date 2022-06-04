#pragma once
#include "Game.h"
#include <SFML/Graphics.hpp>
#include "UI.h"
#include "Game.h"

class Application
{
public:
	Application();
	int run();
	int shutdown();

	struct Mouse
	{
		sf::Vector2f pos;
		bool clicked_left = false;
		bool clicked_right = false;
		bool pressed_left = false;
		bool pressed_right = false;
	};
	Mouse mouse;

	enum ApplicationState
	{
		STATE_UI = 0,
		STATE_GAME = 1
	};

	int State = ApplicationState::STATE_UI;
	sf::RenderWindow window;

	int window_width = 800;
	int window_height = 600;

	UI ui = UI(this);
	Game game = Game(this);
private:

	void updateUserInputs(sf::Event _event);
	void createWindow();

	int fps = 60;
};