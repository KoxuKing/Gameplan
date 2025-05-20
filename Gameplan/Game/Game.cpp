#include "Game.h"
#include "../application.h"
#include <iostream>
#include "ConnectFourPlayer.h"
#include "CheckersTable.h"
#include "CheckersPlayer.h"

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
		application->clock.restart();
		table.reset(new ConnectFourTable());
		isGameSelected = true;

		playerList.clear();
		playerList.push_back(std::make_unique<ConnectFourPlayer>());
		playerList.push_back(std::make_unique<ConnectFourPlayer>());
		playerList[0]->data.isTurn = true;
	}
	else if (gameName == "Checkers" && !isGameSelected)
	{
		application->clock.restart();
		table.reset(new CheckersTable());
		isGameSelected = true;
		playerList.clear();
		playerList.push_back(std::make_unique<CheckersPlayer>(1));
		playerList.push_back(std::make_unique<CheckersPlayer>(2));
			
		playerList[0]->data.isTurn = true; // 1st players starts
		playerList[1]->data.isTurn = false; // 1st players starts
	}
		
	// DEBUG MODE
	//state = GameState::STATE_DEBUG;

	switch(state)
	{
		case GameState::STATE_LOBBY:
			if (playerList.size() >= requiredPlayers)
				state = GameState::STATE_GAME;

			break;
		case GameState::STATE_GAME:
			for (const auto& player : playerList)
			{
				if (player->data.isTurn)
					table->update(player.get(), application);
			}
			break;
		case GameState::STATE_DEBUG:
		
			for (const auto& player : playerList)
			{
				if (player->data.isTurn)
					table->update(player.get(), application);
			}
			break;
	}

}

void Game::changePlayerTurn(Player* active_player)
{
	bool turn_changed = false;
	bool turn_found = false;

	while (!turn_changed)
	{
		for (const auto& player : playerList)
		{
			if (active_player->data.playerNumber == player->data.playerNumber)
			{
				player->data.isTurn = false;
				turn_found = true;
			}
			else if (turn_found)
			{
				player->data.isTurn = true;
				turn_changed = true;
			}

		}
	}
}

void Game::connectToServer(sf::IpAddress _address, int _port)
{
	//client.connectToServer(_address, _port);
}


void Game::shutdown()
{
	//for (const auto& player : playerList)
		//delete player;
	//delete table;
}

void Game::updatePlayersCallback(Player::gameData& _data)
{
	// Ensimmäinen viesti on aina tälle pelaajalle
	// Viestistä otetaan talteen pelaajan numero
	if (playerList.size() < requiredPlayers)
		playerList.push_back(std::make_unique<Player>());
	for (const auto& player : playerList)
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
	if (!isGameOn)
		unfocusGame();
	else if (isGameOn)
		focusGame();

}

void Game::unfocusGame()
{
	rect.setFillColor(sf::Color(50, 50, 50, 255));
	if (table)
		table->unfocusTable();
}

void Game::focusGame()
{
	rect.setFillColor(sf::Color(255, 255, 255, 255));
	if (table)
		table->focusTable();
}
