#pragma once

struct gameData
{
	int playerNumber;
	int playerTurn;
	int players;
	int tokenPos;
	bool isTurn;
	// table data
};

class Player
{
public:
	gameData data;
};
