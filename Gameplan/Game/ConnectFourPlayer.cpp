#include "ConnectFourPlayer.h"
#include "ConnectFourTable.h"

void ConnectFourPlayer::dropToken(ConnectFourTable& _table, int _column, int _player)
{
	// Goes through every row
	for (int row = 0; row < _table.lastRow; row++)
	{
		// Checks if there is a token at next row or if it is next to a border
		if (_table.board[row + 1][_column] != 0 || row + 1 == _table.lastRow)
		{
			// Puts a token to the right place of the board
			_table.board[row][_column] = _player;

			// Pushes new token to vector
			_table.tokenVector.push_back(new Token(row, _column, _player));

			// Checks if there comes straight from that token
			if (_table.isStraight(row, _column))
			{
				std::cout << "Straight found, Game over!" << std::endl;
			}

			break;
		}
	}
}
