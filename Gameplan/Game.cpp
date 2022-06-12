#include "Game.h"
#include "application.h"

Game::Game(Application* _application)
{
	application = _application;
	// Luo pelaajan, pelipöydän ja taustakuvan

}

void Game::update()
{
	//drawBackground();
	switch(state)
	{
	case GameState::STATE_LOBBY:
		if (playerList.size() >= requiredPlayers)
			state = GameState::STATE_GAME;

		break;
	case GameState::STATE_GAME:
		for (Player* player : playerList)
		{
			if (player->data.isTurn)
				table.update(player);
		}

		break;
	case GameState::STATE_ENDMENU:
		// Voittajan ilmoitus, pelin uusinta, (pelin vaihto), 
		break;
	}
}

void Game::shutdown()
{
}

void Game::updatePlayersCallback(gameData& _data)
{
	// Ensimmäinen viesti on aina tälle pelaajalle
	// Viestistä otetaan talteen pelaajan numero
	if (playerList.size() < requiredPlayers)
		playerList.push_back(new Player);
	for (Player* player : playerList)
	{
		if (_data.playerNumber == player->data.playerNumber)
			player->data = _data;
	}
	
}

void Game::waitingPlayers()
{
	//
}
