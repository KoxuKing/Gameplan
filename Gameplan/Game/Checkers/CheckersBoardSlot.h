#pragma once
#include "../../application.h"
#include "CheckersPawn.h"

struct BoardSlot {
public:

	BoardSlot(sf::Color color, bool hasPawn, CheckersPawn pawn = CheckersPawn(sf::Color::Black, { -1,-1 }))
		: color(color), hasPawn(hasPawn), pawn(pawn) {}

	sf::Color color;
	CheckersPawn pawn;
	sf::Vector2f position = {0,0};

	bool hasPawn = false;

};