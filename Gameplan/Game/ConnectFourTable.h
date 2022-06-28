#pragma once
#include "GameTable.h"
class ConnectFourTable : public GameTable
{
public:
	ConnectFourTable();
	virtual void update(class ConnectFourPlayer* _player, class Application* _application);

	const static int lastRow = 6;
	const static int lastColumn = 7;

	int board[lastRow][lastColumn] =
	{
	{0, 0, 0, 0, 0, 0, 0},
	{0, 0, 0, 0, 0, 0, 0},
	{0, 0, 0, 0, 0, 0, 0},
	{0, 0, 0, 0, 0, 0, 0},
	{0, 0, 0, 0, 0, 0, 0},
	{0, 0, 0, 0, 0, 0, 0}
	};

	bool isStraight(int _row, int _column);
	
protected:
	virtual void drawTable(class Application* _application);

private:
	const int getColumn(int _mousePosX);
	
};

