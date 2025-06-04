#include "../../application.h"
#include "CheckersTable.h"
#include "CheckersPlayer.h"

void CheckersTable::update(Player* _player, class Application* _application)
{
	if (_application->game.isGameOn)
	{
		if (_application->mouse.clicked_left)
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

					bool can_player_eat = canPlayerEat(dynamic_cast<CheckersPlayer*>(_player));

					selected_slot.pawn->possible_moves = board.getDiagonalMoves(selected_slot.pawn.get(), dynamic_cast<CheckersPlayer*>(_player), can_player_eat);
				}
				else if (selected_slot.pawn) // isPawnSelected() -> move pawn
				{
					// Walid move clicked with selected pawn -> Move pawn to that square
					bool valid_move = board.MoveSelectedPawnToSquare(selected_slot.pawn, dynamic_cast<CheckersPlayer*>(_player), {column, row});

					if (valid_move) _application->game.changePlayerTurn(_player);
					else selected_slot.pawn->possible_moves.clear(); // No pawn on square -> reset moves
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

bool CheckersTable::canPlayerEat(CheckersPlayer* player)
{
	for (int r = 0; r < ROWS; r++)
	{
		for (int c = 0; c < COLUMNS; c++)
		{
			if (board.slots[r][c].pawn && board.slots[r][c].pawn->color == player->color)// board.isPawnInSlot && player->isMyPawn()
			{
				if (board.canPawnEat(board.slots[r][c].pawn.get(), player))
					return true;
			}
		}
	}
	return false;
}
