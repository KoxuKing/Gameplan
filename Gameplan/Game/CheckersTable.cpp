#include "../application.h"
#include "CheckersTable.h"

void CheckersTable::update(class Player* _player, class Application* _application)
{
	if (_application->game.isGameOn)
	{
		if (_application->mouse.clicked_left)
		{
			int column = board.getColumn(_application->mouse.pos.x);
			int row = board.getRow(_application->mouse.pos.y);

			// Selected square has pawn
			if (board.slots[row][column].pawn != nullptr)
			{
				selected_pawn = board.slots[row][column].pawn;
				selected_pawn->board_slot = { column, row };
				board.getPossibleMoves(selected_pawn);
			}
			else if (selected_pawn) // Already selected pawn
			{
				// Walid move clicked with selected pawn -> Move pawn to that square
				bool valid_move = board.MoveSelectedPawnToSquare(selected_pawn, { column, row });

				if (valid_move) std::cout << "Succesful move" << std::endl;
				else selected_pawn->possible_moves.clear(); // No pawn on square -> reset moves
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
	board.DrawPossibleMoves(_application, selected_pawn);
}