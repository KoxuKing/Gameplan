#include "Game.h"
#include "../application.h"
#include "iostream"

Game::Game(Application* _application)
{
	application = _application;
	backgroundImage.loadFromFile("Textures/gameBackground.png");
	size = sf::Vector2f(application->window_width, application->window_height);
	rect.setSize(size);
	rect.setTexture(&backgroundImage);
	// Luo pelaajan, pelipöydän ja taustakuvan

}

void Game::update()
{
	drawGame();
	std::cout << application->mouse.pos.x << application->mouse.pos.y << std::endl;
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
			{
				table.update(player, application);
			}
				
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