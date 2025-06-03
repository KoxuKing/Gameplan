#pragma once
#include "Player.h"
#include "GameTable.h"
#include <vector>
#include <SFML/Graphics.hpp>
#include "ConnectFourTable.h"
#include "../Networking/Client.h"
#include <memory>

class Game
{
public:
	Game(class Application* _application);
	void update();
	void shutdown();
	void selectGame(const std::string& _gameName);
	void changeGame(std::unique_ptr<GameTable> newTable);
	void connectToServer(sf::IpAddress _address, int _port);
	void changePlayerTurn(Player* player);

	enum GameState
	{
		STATE_LOBBY = 0,
		STATE_GAME = 1,
		STATE_DEBUG = 2
	};

	int requiredPlayers = 1;
	int state = GameState::STATE_LOBBY;
	std::vector <std::unique_ptr<Player>> playerList; // Täytyy olla pelikohtainen
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
	std::unique_ptr<GameTable> table;

	sf::RectangleShape rect;		// Taustakuva
	sf::Vector2f size;
	std::string gameName;
};



