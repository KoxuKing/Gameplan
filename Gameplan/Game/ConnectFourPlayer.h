#pragma once
#include "Player.h"

#include <iostream>
class ConnectFourPlayer : public Player
{
public:
	void dropToken(class ConnectFourTable &_table, int _column, int _player);
	virtual struct gameData
	{
		int playerNumber;
		int playerTurn;
		int players;
		int tokenPos;
		bool isTurn;
		// table data
	};


private:
};


