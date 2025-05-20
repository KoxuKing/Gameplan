#pragma once
#include "Player.h"

#include <iostream>
struct ConnectFourPlayer : public Player
{
	void dropToken(class ConnectFourTable &_table, int _column, int _player);
	//void takeToken();
	struct gameData
	{
		int playerNumber;
		int playerTurn;
		int players;
		int tokenPos;
		bool isTurn;
		// table data
	} override;

	std::vector <std::unique_ptr<ConnectFourPlayer>> playerList; // Täytyy olla pelikohtainen

private:
	void dropTokenAnimation();
};


