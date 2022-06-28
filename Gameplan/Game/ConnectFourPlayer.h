#pragma once
#include "Player.h"
class ConnectFourPlayer : public Player
{
public:
	void dropToken(class ConnectFourTable &_table, int _column);
	virtual struct gameData
	{
		int playerNumber;
		int playerTurn;
		int players;
		int tokenPos;
		bool isTurn;
		// table data
	};
};

