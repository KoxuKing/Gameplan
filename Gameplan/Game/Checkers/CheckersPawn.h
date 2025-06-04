#pragma once
#include "../../application.h"

struct CheckersPawn {

public:
	CheckersPawn(sf::Color color, sf::Vector2i board_slot) : color(color), board_slot(board_slot) {}

	bool HasThisMove(sf::Vector2i move)
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
};