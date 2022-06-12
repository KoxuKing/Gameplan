#include "GameTable.h"
#include "application.h"

GameTable::GameTable()
{
	tableTexture.loadFromFile("Textures/testTable.png");
	tableSprite.setTexture(tableTexture);
	tableSprite.setPosition(80, -60);
}

void GameTable::update(Player* _player, Application* _application)
{
	drawTable(_application);
}

void GameTable::shutdown()
{
}

void GameTable::drawTable(Application* _application)
{
	_application->window.draw(tableSprite);
}
