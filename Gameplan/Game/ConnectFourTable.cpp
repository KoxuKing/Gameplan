#include "ConnectFourTable.h"
#include "../application.h"
#include "ConnectFourPlayer.h"

ConnectFourTable::ConnectFourTable()
{
	tableTexture.loadFromFile("Textures/gameTable.png");
	tableSprite.setTexture(tableTexture);
	tableSprite.setPosition(100, 80);
	// Uutta -->
	addTokenArea.setSize(sf::Vector2f(tableSprite.getGlobalBounds().width - 99.0f, 420.0f));
	addTokenArea.setPosition(sf::Vector2f(tableSprite.getPosition().x + 22, tableSprite.getPosition().y - 100));
	//addTokenArea.setFillColor(sf::Color::Green);
	turnTime.setPosition(700, 5);
	turnTime.setCharacterSize(20);
	static sf::Font font;
	font.loadFromFile("Fonts/testiFontti.ttf");
	turnTime.setFont(font);
	turnTime.setFillColor(sf::Color::Black);
	tokenTextures[0].loadFromFile("Textures/redToken.png");
	tokenTextures[1].loadFromFile("Textures/yellowToken.png");

	float tokenScale = 1.9;
	redTokenSprite.setTexture(tokenTextures[0]);
	redTokenSprite.setScale(tokenScale, tokenScale);
	yellowTokenSprite.setTexture(tokenTextures[1]);
	yellowTokenSprite.setScale(tokenScale, tokenScale);

}

void ConnectFourTable::update(Player* _player, Application* _application)
{
	if (_application->game.isGameOn && !isAnimationOn)
	{
		if (_application->mouse.clicked_left && addTokenArea.getGlobalBounds().contains(_application->mouse.pos))
		{
			int column = getColumn(_application->mouse.pos.x);

			if (board[0][column] != 0)
				std::cout << "Column is already full" << std::endl;
			else
				static_cast<ConnectFourPlayer*>(_player)->dropToken(*this, getColumn(_application->mouse.pos.x), _player->data.playerNumber);
		}
	}

	turnTime.setString("Time: " + std::to_string(int(_application->timePassed.asSeconds())));
	_application->window.draw(turnTime);
	playAnimation(_application);
	drawTokens(_application);
	drawTable(_application);
}

void ConnectFourTable::unfocusTable()
{
	tableSprite.setColor(sf::Color(50, 50, 50, 255));
	redTokenSprite.setColor(sf::Color(50, 50, 50, 255));
	yellowTokenSprite.setColor(sf::Color(50, 50, 50, 255));

}
void ConnectFourTable::focusTable()
{
	tableSprite.setColor(sf::Color(255, 255, 255, 255));
	redTokenSprite.setColor(sf::Color(255, 255, 255, 255));
	yellowTokenSprite.setColor(sf::Color(255, 255, 255, 255));
}


/*void ConnectFourTable::shutdown()
{
	for (Token* token : tokenVector)
		delete token;

	tokenVector.clear();
}*/

const int ConnectFourTable::getColumn(int _mousePosX)
{
	const int mousePosXOnBoard = _mousePosX - addTokenArea.getPosition().x; // Calculates mouse x position on a board, position is 0 at left border of board
	float columnWidth = addTokenArea.getSize().x / lastColumn; // Calculates width of a column
	float rowHeight = addTokenArea.getSize().y / lastRow; // Calculates height of a row

	// Goes through every column
	for (int column = 1; column <= 7; column++) 
	{
		// Checks on which column mouse currently is
		if (mousePosXOnBoard < column * columnWidth && mousePosXOnBoard > column - 1 * columnWidth)
		{
			// Returns columns - 1 because columns are 0-6 in array
			return column - 1;
		}
	}

	return 0;
}



bool ConnectFourTable::isStraight(int _row, int _column)
{
	int token = board[_row][_column];		// Number of player's token
	int rowNumber = _row;
	int columnNumber = _column;
	int tokensConnected = 0;				// Amount of tokens that are connected, starts with 0

	if (token != 0)
	{
		for (int i = 1; i <= 7; i++)
		{
			/*
			* Goes to while loop 7 times and checks if there is straight from
			* 1. horizontally to right
			* 2. horizontally to left
			* 3. diagonally to up right
			* 4. diagonally to down left
			* 5. diagonally to down right
			* 6. diagonally to up left
			* 7. vertically down
			*/

			// Checks if a token is from the same player, else goes to next round of for loop
			while (board[rowNumber][columnNumber] == token)
			{
				if (i == 1 || i == 3 || i == 5)
					columnNumber++;

				if (i == 4 || i == 5 || i == 7)
					rowNumber++;
				
				if (i == 2 || i == 4 || i == 6)
					columnNumber--;

				if (i == 3 || i == 6)
					rowNumber--;

				tokensConnected++;


				if (tokensConnected >= 4)
				{
					std::cout << tokensConnected << std::endl;
					return true;
				}
			}

			// Restores used values to starting point
			token = board[_row][_column];
			rowNumber = _row;
			columnNumber = _column;

			if (i % 2 == 0) // if i is pairless it means we aren't checking same row
				tokensConnected = 0;
			else if (i % 2 == 1)	// if i is pair it mean we are checking same row
				tokensConnected--;
		}
	}
	return false;
}


void ConnectFourTable::drawTable(Application* _application)
{
	_application->window.draw(tableSprite);
	//_application->window.draw(addTokenArea);
}

void ConnectFourTable::playAnimation(Application* _application)
{
	if (isAnimationOn)
		dropTokenAnimation(_application);
	else
	{
		animationStartTime = _application->timePassed.asSeconds();

		// Checks if there comes straight from that token
		if (isStraight(latestToken.x, latestToken.y))
		{
			_application->ui.State = UI::UiState::STATE_ENDGAME;
			_application->game.isGameOn = false;
			latestToken = sf::Vector2i(-1, -1);
			for (int i = 0; i < lastColumn; i++)
				for (int j = 0; j < lastRow; j++)
					board[j][i] = 0;
		}
	}
}

void ConnectFourTable::drawTokens(Application* _application)
{
	tokenPos;
	tokenPos = sf::Vector2f(tableSprite.getPosition().x + 30 + getColumn(_application->mouse.pos.x) * 57, tableSprite.getPosition().y + 7 - 1 * 53);
	for (const auto& player : _application->game.playerList)
	{
		if (player->data.playerNumber == 1 && player->data.isTurn)
		{
			redTokenSprite.setPosition(tokenPos);
			_application->window.draw(redTokenSprite);
		}
		else if (player->data.playerNumber == 2 && player->data.isTurn)
		{
			yellowTokenSprite.setPosition(tokenPos);
			_application->window.draw(yellowTokenSprite);
		}
	}

	for (int row = 0; row < lastRow; row++)
	{
		for (int column = 0; column < lastColumn; column++)
		{
			tokenPos = sf::Vector2f(tableSprite.getPosition().x + 30 + column * 57, tableSprite.getPosition().y + 7 + row * 53);
			if (board[row][column] == 1)
			{
				redTokenSprite.setPosition(tokenPos);
				_application->window.draw(redTokenSprite);
			}
			else if (board[row][column] == 2)
			{
				yellowTokenSprite.setPosition(tokenPos);
				_application->window.draw(yellowTokenSprite);
			}
		}
	}
}

void ConnectFourTable::dropTokenAnimation(Application* _application)
{
	sf::Vector2f targetPos = sf::Vector2f(tableSprite.getPosition().x + 30 + latestToken.y * 57, tableSprite.getPosition().y + 7 + latestToken.x * 53);
	sf::Vector2f drawPos = sf::Vector2f(tableSprite.getPosition().x + 30 + latestToken.y * 57, tableSprite.getPosition().y + 7 + animationPos * 53);
	
	// Adds acceleration to animation
	animationPos += 0.00 + 0.4 * (_application->timePassed.asSeconds() - animationStartTime);
	for (const auto& player : _application->game.playerList)
	{
		if (player->data.isTurn)
		{
			if(player->data.playerNumber == 1)
			{
				redTokenSprite.setPosition(drawPos);
				_application->window.draw(redTokenSprite);
			}
			else if (player->data.playerNumber == 2)
			{
				yellowTokenSprite.setPosition(drawPos);
				_application->window.draw(yellowTokenSprite);
			}

			if (animationPos >= latestToken.x)
			{
				isAnimationOn = false;
				_application->clock.restart();
				board[latestToken.x][latestToken.y] = player->data.playerNumber;
				animationPos = 0;
			}
		}
	}
	
}