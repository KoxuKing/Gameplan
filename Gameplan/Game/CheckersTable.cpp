#include "../application.h"
#include "CheckersTable.h"
#include "CheckersPlayer.h"

void CheckersTable::update(class Player* _player, class Application* _application)
{
	if (_application->game.isGameOn)
	{
		if (_application->mouse.clicked_left)
		{
			int column = board.getColumn(_application->mouse.pos.x);
			int row = board.getRow(_application->mouse.pos.y);

			if (row > -1 && column > -1)
			{
				// Selected square has pawn
				if (board.slots[row][column].hasPawn)
				{
					selected_slot = board.slots[row][column];
					selected_slot.pawn.board_slot = { column, row };
					// can player eat -> force to eat
					bool can_palyer_eat = canPlayerEat(dynamic_cast<CheckersPlayer*>(_player));
					//std::cout << can_palyer_eat << std::endl;
					board.getDiagonalMoves(selected_slot.pawn, dynamic_cast<CheckersPlayer*>(_player), can_palyer_eat);
				}
				else if (selected_slot.hasPawn) // Already selected pawn
				{
					// Walid move clicked with selected pawn -> Move pawn to that square
					bool valid_move = board.MoveSelectedPawnToSquare(selected_slot.pawn, dynamic_cast<CheckersPlayer*>(_player), { column, row });

					if (valid_move) _application->game.changePlayerTurn(_player);
					else selected_slot.pawn.possible_moves.clear(); // No pawn on square -> reset moves
				}
			}
		}
	}

	drawTable(_application);
}

void CheckersTable::unfocusTable()
{
	;
}
void CheckersTable::focusTable()
{
	;
}

void CheckersTable::drawTable(class Application* _application)
{
	board.DrawBoard(_application);
	board.DrawPawns(_application);
	board.DrawPossibleMoves(_application, selected_slot);
}
