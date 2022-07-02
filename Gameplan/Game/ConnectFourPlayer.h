#pragma once
#include "Player.h"

#include <iostream>
class ConnectFourPlayer : public Player
{
public:
	void dropToken(class ConnectFourTable &_table, int _column, int _player);
	virtual struct gameData
	{
		int playerNumber;
		int playerTurn;
		int players;
		int tokenPos;
		bool isTurn;
		// table data
	};


private:

};

struct Token  // Uutta
{
	sf::Sprite tokenSprite;
	sf::Texture tokenTexture;

	Token(int _row, int _column, int _playerNumber)
	{	
		if (_playerNumber == 1)
			tokenTexture.loadFromFile("Textures/redToken.png");
		else if (_playerNumber == 2)
			tokenTexture.loadFromFile("Textures/yellowToken");
		else
			std::cout << "Could not set texture to token, no player number?";
		
		tokenSprite.setTexture(tokenTexture);

		tokenSprite.setPosition(sf::Vector2f(_column * 15, _row * 10));  // Tähän joku parempi mekaniikka
	}
};
