#pragma once
#include "GameTable.h"
#include <vector>

class CheckersTable : public GameTable
{
public:
	CheckersTable()
	{
		board = {
		   {0, 1, 0, 1, 0, 1, 0, 1},
		   {1, 0, 1, 0, 1, 0, 1, 0},
		   {0, 1, 0, 1, 0, 1, 0, 1},
		   {1, 0, 1, 0, 1, 0, 1, 0},
		   {0, 1, 0, 1, 0, 1, 0, 1},
		   {1, 0, 1, 0, 1, 0, 1, 0},
		   {0, 1, 0, 1, 0, 1, 0, 1},
		   {1, 0, 1, 0, 1, 0, 1, 0}
		};
	}

	void update(class Player* _player, class Application* _application) override;
	void unfocusTable() override;
	void focusTable() override;


	const int RECT_SIZE = 50;
	const int ROWS = 8;
	const int COLUMNS = 8;

	// Initialize the 2D vector board
	std::vector<std::vector<int>> board;

protected:
	void drawTable(class Application* _application) override;

private:
	sf::RectangleShape addTokenArea;
	float animationStartTime;

	const int getColumn(int _mousePosX);
	const int getRow(int _mousePosY);

	void drawTokens(Application* _application);
	void dropTokenAnimation(Application* _application);
	void playAnimation(Application* _application);
	float animationPos{};
};