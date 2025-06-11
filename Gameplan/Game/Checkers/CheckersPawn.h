#pragma once
#include "../../application.h"

class CheckersPawn {

public:
	CheckersPawn(sf::Color color, sf::Vector2i board_slot) 
		: color(color), board_slot(board_slot), isKing(false) {}

	bool HasThisMove(sf::Vector2i move) const
	{
		for (int i = 0; i < possible_moves.size(); i++)
		{
			if (possible_moves[i] == move)
				return true;
		}
		return false;
	}

	sf::Color color;
	std::vector<sf::Vector2i> possible_moves;
	sf::Vector2i board_slot;
	bool isKing; // New field to track king status
};