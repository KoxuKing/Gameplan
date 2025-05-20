#pragma once
#include <SFML/Graphics.hpp>

struct Player
{
	virtual struct gameData
	{
		int playerNumber = 0;
		int playerTurn = 0;
		int players = 0;
		bool isTurn = false;
	};

	virtual ~Player() {}

	gameData data;
};
