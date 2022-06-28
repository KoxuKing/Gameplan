#include "ConnectFourTable.h"
#include "../application.h"
#include "ConnectFourPlayer.h"

ConnectFourTable::ConnectFourTable()
{
	tableTexture.loadFromFile("Textures/testTable.png");
	tableSprite.setTexture(tableTexture);
	tableSprite.setPosition(80, -60);
}

void ConnectFourTable::update(ConnectFourPlayer* _player, Application* _application)
{
	if (_application->mouse.clicked_left)
	{
		_player->dropToken(*this, getColumn(_application->mouse.pos.x), _player->data.playerNumber);
	}
	drawTable(_application);
}

const int ConnectFourTable::getColumn(int _mousePosX)
{
	return 0;
}

bool ConnectFourTable::isStraight(int _row, int _column)
{
	int token = board[_row][_column];		// Number of player's token
	int rowNumber = _row;
	int columnNumber = _column;
	int tokensConnected = 0;				// Amount of tokens that are connected, starts with 0

	for (int i = 1; i <= 7; i++)
	{
		/*
		* Goes to while loop 7 times and checks if there is straight from
		* 1. horizontally to right
		* 2. horizontally to left
		* 3. vertically down
		* 4. diagonally to down right
		* 5. diagonally to down left
		* 6. diagonally to up right
		* 7. diagonally to up left
		*/

		// Checks if a token is from the same player, else goes to next round of for loop
		while (board[rowNumber][columnNumber] == token)
		{
			if (i == 1 || i == 5 || i == 6)
				columnNumber++;

			if (i == 3 || i == 4 || i == 5)
				rowNumber++;

			if (i == 2 || i == 5 || i == 7)
				columnNumber--;

			if (i == 6 || i == 7)
				rowNumber--;

			tokensConnected++;

			if (tokensConnected >= 4)
			{
				return true;
			}
		}

		// Restores used values to starting point
		token = board[_row][_column];
		rowNumber = _row;
		columnNumber = _column;
		tokensConnected = 0;
	}
	return false;
}

void ConnectFourTable::drawTable(Application* _application)
{
	_application->window.draw(tableSprite);
}
