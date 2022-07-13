#pragma once
#include "Player.h"
#include "GameTable.h"
#include <vector>
#include <SFML/Graphics.hpp>
#include "ConnectFourTable.h"
#include "../Networking/Client.h"

class Game
{
public:
	Game(class Application* _application);
	void update();
	void shutdown();
	void selectGame(const std::string& _gameName);
	void connectToServer(sf::IpAddress _address, int _port);
	enum GameState
	{
		STATE_LOBBY = 0,
		STATE_GAME = 1,
		STATE_DEBUG = 2
	};
	int requiredPlayers = 2;
	int state = GameState::STATE_LOBBY;
	std::vector <Player*> playerList;
	//Client client; // TÄSSÄ VIKA!!! //
	bool isGameOn = true;

	
private:
	sf::Texture backgroundImage;
	void updatePlayersCallback(Player::gameData& data);
	void waitingPlayers();
	void drawGame();
	void unfocusGame();
	void focusGame();

	bool isGameSelected;
	class Application* application;
	GameTable *table;

	sf::RectangleShape rect;		// Taustakuva
	sf::Vector2f size;
	std::string gameName;
};



