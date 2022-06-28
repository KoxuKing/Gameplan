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
		_player->dropToken(*this, getColumn(_application->mouse.pos.x));
	}
	drawTable(_application);
}

const int ConnectFourTable::getColumn(int _mousePosX)
{

}

void ConnectFourTable::drawTable(Application* _application)
{
	_application->window.draw(tableSprite);
}
