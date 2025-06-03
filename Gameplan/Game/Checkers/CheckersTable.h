#pragma once
#include "../GameTable.h"
#include "CheckersBoard.h"
#include <vector>
#include <memory>


class CheckersTable : public GameTable
{
public:
	CheckersTable(){}

	void update(Player* _player, class Application* _application) override;
	void unfocusTable() override;
	void focusTable() override;

	bool canPlayerEat(CheckersPlayer* player);

	const int ROWS = 8;
	const int COLUMNS = 8;

	// Initialize the 2D vector board
	CheckersBoard board = CheckersBoard({ ROWS ,COLUMNS });
	BoardSlot selected_slot = BoardSlot(sf::Color::Black, false);

protected:
	void drawTable(class Application* _application) override;


	
};

