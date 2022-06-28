#pragma once
#include "GameTable.h"
class ConnectFourTable : public GameTable
{
public:
	ConnectFourTable();
	virtual void update(class ConnectFourPlayer* _player, class Application* _application);

protected:
	virtual void drawTable(class Application* _application);

private:
	const int getColumn(int _mousePosX);
};

