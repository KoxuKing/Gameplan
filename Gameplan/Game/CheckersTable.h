#pragma once
#include "GameTable.h"
#include "Checkers.h"
#include <vector>
#include <memory>


class CheckersTable : public GameTable
{
public:
	CheckersTable(){}

	void update(class Player* _player, class Application* _application) override;
	void unfocusTable() override;
	void focusTable() override;

	bool canPlayerEat(CheckersPlayer* player)
	{
		for (int r = 0; r < ROWS; r++)
		{
			for (int c = 0; c < COLUMNS; c++)
			{
				if (board.slots[r][c].hasPawn && board.slots[r][c].pawn.color == player->color)
				{
					if (board.canPawnEat(board.slots[r][c].pawn, player))
						return true;
				}
			}
		}
		return false;
	}

	const int ROWS = 8;
	const int COLUMNS = 8;

	// Initialize the 2D vector board
	CheckersBoard board = CheckersBoard({ ROWS ,COLUMNS });
	BoardSlot selected_slot = BoardSlot(sf::Color::Black, false);

	//std::vector <std::unique_ptr<CheckersPlayer>> playerList; // Täytyy olla pelikohtainen

protected:
	void drawTable(class Application* _application) override;


	
};

