#pragma once
#include "../Player.h"
#include <iostream>

struct CheckersPlayer : public Player
{
	CheckersPlayer(int playerNumber){
		if (playerNumber == 1)
			color = sf::Color::Red;
		else color = sf::Color::Yellow;

		data.playerNumber = playerNumber;
	}

	sf::Color color;
};
