#pragma once
#include <vector>
#include <memory>
#include <SFML/Graphics.hpp>

class UI
{
public:
	UI(class Application* _application);
	int update();
	int shutdown();

	enum UiState
	{
		STATE_MAIN_MENU = 0,
		STATE_OPTIONS = 1,
		STATE_QUIT = 2,
		STATE_GAME_SELECTION = 3,
		STATE_GAME = 4,
		STATE_ENDGAME = 5,
		STATE_GAME_MENU = 6,
	};

	int State = UiState::STATE_MAIN_MENU;
	int previousState = UiState::STATE_MAIN_MENU;

	std::unique_ptr<class Window> endGameWindow;
private:
	class Application* application;

	class Window* activeWindow = nullptr;
	std::unique_ptr<class Window> mainmenu;
	std::unique_ptr<class Window> options;
	std::unique_ptr<class Window> gameSelection;
	std::unique_ptr<class Window> lobby;
	std::unique_ptr<class Window> inGame;
	std::unique_ptr<class Window> inGameMenu;

	sf::Texture backgroundImage;

	void drawUi();
	void checkButtons();
};

struct Window
{
	Window(std::string _texturePath, int _x, int _y, int _width, int _height)
	{
		width = _width;
		height = _height;
		x = _x;
		y = _y;
		texturePath = _texturePath;
	}

	int width;
	int height;
	int x;
	int y;
	std::string texturePath{};

	std::vector<class UiInput*> buttonList;
};