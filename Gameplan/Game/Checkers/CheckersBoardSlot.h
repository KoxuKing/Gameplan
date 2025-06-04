#pragma once
#include "../../application.h"
#include "CheckersPawn.h"

struct BoardSlot {
public:

	BoardSlot(sf::Color _color, std::shared_ptr<CheckersPawn> _pawn = nullptr)
	{
		color = _color;
		if (_pawn)
			pawn = _pawn;
	}

	sf::Color color;
	std::shared_ptr<CheckersPawn> pawn = nullptr;
	sf::Vector2f position = {0,0};

	//bool hasPawn = false;

};