#pragma once
#include "Player.h"
#include "GameTable.h"
#include <vector>

class Game
{
public:
	Game(class Application* _application);
	void update();
	void shutdown();

	enum GameState
	{
		STATE_LOBBY = 0,
		STATE_GAME = 1,
		STATE_ENDMENU = 2
	};

	int requiredPlayers = 2;
	int state = GameState::STATE_LOBBY;
	std::vector <Player*> playerList;

private:
	void updatePlayersCallback(gameData& data);
	void waitingPlayers();
	class Application* application;
	GameTable table;
};

