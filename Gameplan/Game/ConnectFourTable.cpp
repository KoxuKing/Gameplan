#include "ConnectFourTable.h"
#include "../application.h"
#include "ConnectFourPlayer.h"

ConnectFourTable::ConnectFourTable()
{
	tableTexture.loadFromFile("Textures/gameTable.png");
	tableSprite.setTexture(tableTexture);
	tableSprite.setPosition(100, 30);

	// Uutta -->
	addTokenArea.setSize(sf::Vector2f(tableSprite.getGlobalBounds().width - 70.0f, -100.0f));
	addTokenArea.setPosition(tableSprite.getPosition());
	addTokenArea.setFillColor(sf::Color::Green);
}

void ConnectFourTable::update(Player* _player, Application* _application)
{

	// EI OLE VIELÄ TESTATTU //
	if (_application->mouse.clicked_left && addTokenArea.getGlobalBounds().contains(_application->mouse.pos))
	{
		std::cout << "paneittu!" << std::endl;
		static_cast<ConnectFourPlayer*>(_player)->dropToken(*this, getColumn(_application->mouse.pos.x), _player->data.playerNumber);
	}
	drawTable(_application);

	// EI OLE VIELÄ TESTATTU //
}

const int ConnectFourTable::getColumn(int _mousePosX)
{
	// EI OLE VIELÄ TESTATTU //

	const int columnWidth = addTokenArea.getSize().x / lastColumn; // Calculates width of a column
	const int mousePosXOnBoard = _mousePosX - tableSprite.getPosition().x; // Calculates mouse x position on a board, position is 0 at left border of board

	// Goes through every column
	for (int column = 1; column <= 7; column++) 
	{
		// Checks on which column mouse currently is
		if (mousePosXOnBoard < column * columnWidth && mousePosXOnBoard > column - 1 * columnWidth)
		{
			// Returns columns -1 because columns are 0-6 in array
			return column - 1;
		}
	}

	// EI OLE VIELÄ TESTATTU //

	return 0;
}

bool ConnectFourTable::isStraight(int _row, int _column)
{
	int token = board[_row][_column];		// Number of player's token
	int rowNumber = _row;
	int columnNumber = _column;
	int tokensConnected = 0;				// Amount of tokens that are connected, starts with 0

	for (int i = 0; i < lastRow; i++)
	{
		for (int r = 0; r < lastColumn; r++)
		{
			std::cout << board[i][r];
		}
		std::cout << std::endl;
	}

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
			if (i == 1 || i == 4 || i == 6)
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
	_application->window.draw(addTokenArea);
}
