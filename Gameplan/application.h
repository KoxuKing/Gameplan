#pragma once
#include "Game/Game.h"
#include <SFML/Graphics.hpp>
#include "UI/UI.h"

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

	struct Keyboard
	{
		bool isKeyPressed;
		bool isKeyReleased;
		float timeHolded;
		char pressedKey;
		unsigned int keyUnicode;
	};
	Keyboard keyboard;

	enum ApplicationState
	{
		STATE_UI = 0,
		STATE_GAME = 1,
		STATE_SHUTDOWN = 2
	};

	int State = ApplicationState::STATE_UI;
	sf::RenderWindow window;

	int window_width = 800;
	int window_height = 600;

	UI ui = UI(this);
	Game game = Game(this);

	float volume = 10;
	sf::Event event;
	sf::Clock clock;
	sf::Time timePassed;
private:

	void updateUserInputs(sf::Event& _event);
	float startTime = 0;
	int fps = 120;
};