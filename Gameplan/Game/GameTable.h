#pragma once
#include "Player.h"
#include <SFML/Graphics.hpp>

class GameTable
{
public:
	GameTable();
	virtual void update(Player* _player, class Application* _application);
	virtual void shutdown();
	

protected:
	virtual void drawTable(class Application* _application);
	sf::Sprite tableSprite;
	sf::Texture tableTexture;
private:

	
};

