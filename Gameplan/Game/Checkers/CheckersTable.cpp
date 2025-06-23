#include "../../application.h"
#include "CheckersTable.h"
#include "CheckersPlayer.h"
#include "CheckersAI/CheckersAI.h"

void CheckersTable::update(Player* _player, class Application* _application)
{
	if (_application->game.isGameOn)
	{
		if (dynamic_cast<CheckersAI*>(_player))
		{
			// AI's turn
			CheckersAI* ai = dynamic_cast<CheckersAI*>(_player);
			
			// AI makes a move
			bool valid_move = ai->makeMove(board, this);

			if (valid_move) _application->game.changePlayerTurn(_player);

		}
		
		else if (_application->mouse.clicked_left)
		{

			// Get clicked slot's column and row
			int column = board.getColumn(_application->mouse.pos.x);
			int row = board.getRow(_application->mouse.pos.y);

			if (board.isSlotValid({row, column}))
			{
				// Selected square has pawn -> select it
				if (board.slots[row][column].pawn) // board.isPawnInSlot({row, column})
				{
					selected_slot = board.slots[row][column]; // board.getSlot({row, column})

					bool can_player_eat = board.canPlayerEat(dynamic_cast<CheckersPlayer*>(_player));

					selected_slot.pawn->possible_moves = board.getDiagonalMoves(selected_slot.pawn.get(), dynamic_cast<CheckersPlayer*>(_player), can_player_eat);
				}
				else if (selected_slot.pawn) // isPawnSelected() -> move pawn
				{
					// Walid move clicked with selected pawn -> Move pawn to that square
					bool valid_move = board.moveSelectedPawnToSquare(selected_slot.pawn.get(), dynamic_cast<CheckersPlayer*>(_player), {column, row});

					if (valid_move) _application->game.changePlayerTurn(_player);
					
					selected_slot.pawn->possible_moves.clear();
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
	board.drawBoard(_application);
	board.drawPawns(_application);
	board.drawPossibleMoves(_application, selected_slot);
}


