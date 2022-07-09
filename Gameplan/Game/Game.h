#pragma once
#include "Player.h"
#include "GameTable.h"
#include <vector>
#include <SFML/Graphics.hpp>
#include "ConnectFourTable.h"

class Game
{
public:
	Game(class Application* _application);
	void update();
	void shutdown();
	void selectGame(const std::string& _gameName);

	enum GameState
	{
		STATE_LOBBY = 0,
		STATE_GAME = 1,
		STATE_ENDMENU = 2,
		STATE_DEBUG = 3
	};
	int requiredPlayers = 2;
	int state = GameState::STATE_LOBBY;
	std::vector <Player*> playerList;
	
private:
	sf::Texture backgroundImage;
	void updatePlayersCallback(Player::gameData& data);
	void waitingPlayers();
	void drawGame();
	bool isGameSelected;
	class Application* application;
	GameTable *table;

	sf::RectangleShape rect;		// Taustakuva
	sf::Vector2f size;
	std::string gameName;
};



