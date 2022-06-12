#pragma once
#include "Player.h"

class GameTable
{
public:
	GameTable();
	virtual void update(Player *_player);
	virtual void shutdown();
};

