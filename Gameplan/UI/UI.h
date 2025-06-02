#pragma once
#include <vector>
#include <memory>
#include <map>
#include <SFML/Graphics.hpp>

class Button;  // Forward declaration
class UiInput;  // Forward declaration for clarity

/**
 * UI Manager Class for Game Platform
 * Handles creation and management of all UI windows and elements
 */
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

private:
	class Application* application;

	// Layout constants
	const int STANDARD_BUTTON_WIDTH = 200;
	const int STANDARD_BUTTON_HEIGHT = 50;
	
	class Window* activeWindow = nullptr;
	std::unique_ptr<class Window> mainmenu;
	std::unique_ptr<class Window> options;
	std::unique_ptr<class Window> gameSelection;
	std::unique_ptr<class Window> lobby;
	std::unique_ptr<class Window> inGame;
	std::unique_ptr<class Window> inGameMenu;
	std::unique_ptr<class Window> endGameWindow;

	sf::Texture backgroundImage;
	std::map<std::string, sf::Texture> textureCache;

	// Helper methods
	void drawUi();
	void checkButtons();
	int centerX(int width) const;
	int centerY(int height) const;
	
	// Texture management
	sf::Texture& getTexture(const std::string& path);
	
	// UI creation methods
	void createMainMenu();
	void createOptionsMenu(); 
	void createGameSelectionMenu();
	void createEndGameWindow();
	void createInGameUI();
	void createInGameMenu();
	void createLobbyWindow();

	void loadBackgroundForState(Window* window);

	Button* createStandardButton(int x, int y, int width, int height, const std::string& text, UiState state, const std::string& texturePath);
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

	// Add destructor to clean up buttonList
	~Window()
	{
		for (UiInput* input : buttonList) {
			delete input;
		}
		buttonList.clear();
	}

	int width;
	int height;
	int x;
	int y;
	std::string texturePath{};

	std::vector<class UiInput*> buttonList;
};