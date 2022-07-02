#pragma once
#include <SFML/Graphics.hpp>

class Player
{
public:
	virtual struct gameData
	{
		int playerNumber;
		int playerTurn;
		int players;
		bool isTurn;
	};
	gameData data;
};
