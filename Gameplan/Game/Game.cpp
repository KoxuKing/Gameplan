#include "Game.h"
#include "../application.h"
#include <iostream>
#include "ConnectFourPlayer.h"

Game::Game(Application* _application)
{
	application = _application;
	backgroundImage.loadFromFile("Textures/gameBackground.png");
	size = sf::Vector2f(application->window_width, application->window_height);
	rect.setSize(size);
	rect.setTexture(&backgroundImage);
}

void Game::selectGame(const std::string& _gameName)
{
	gameName = _gameName;
}

void Game::update()
{
	drawGame();
	if (gameName == "ConnectFour" && !isGameSelected)
	{
		table = new ConnectFourTable();
		isGameSelected = true;
	}
		
	
	// DEBUG MODE
	state = GameState::STATE_DEBUG;

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
				table->update(player, application);
		}
		break;
	case GameState::STATE_DEBUG:
		
		if (playerList.size() == 0)
		{
			playerList.push_back(new Player);
			playerList[0]->data.playerNumber = 1;
		}
			
		for (Player* player : playerList)
		{
			if(!player->data.isTurn && player->data.playerNumber == 1)
				player->data.playerNumber = 2;
			else if (!player->data.isTurn && player->data.playerNumber == 2)
				player->data.playerNumber = 1;

			player->data.isTurn = true;
			if (player->data.isTurn)
				table->update(player, application);
		}
		break;
	}

}

void Game::connectToServer(sf::IpAddress _address, int _port)
{
	client.connectToServer(_address, _port);
}

void Game::shutdown()
{
	for (Player* player : playerList)
		delete player;
	delete table;
}

void Game::updatePlayersCallback(Player::gameData& _data)
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

void Game::drawGame()
{
	application->window.draw(rect);
}