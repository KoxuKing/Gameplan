#pragma once
#include "Player.h"
#include <SFML/Graphics.hpp>

class GameTable
{
public:
	GameTable();
	virtual void update(Player* _player, class Application* _application);
	virtual void shutdown();
	virtual void unfocusTable() = 0;
	virtual void focusTable() = 0;

	

protected:
	virtual void drawTable(class Application* _application);
	sf::Sprite tableSprite;
	sf::Texture tableTexture;

private:

	
};

