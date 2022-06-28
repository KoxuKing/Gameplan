#pragma once

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
