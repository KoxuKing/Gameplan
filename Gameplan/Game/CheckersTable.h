#pragma once
#include "GameTable.h"
#include "Checkers.h"
#include <vector>
#include <memory>


class CheckersTable : public GameTable
{
public:
	CheckersTable()
	{
	}

	void update(class Player* _player, class Application* _application) override;
	void unfocusTable() override;
	void focusTable() override;

	const int ROWS = 8;
	const int COLUMNS = 8;

	// Initialize the 2D vector board
	CheckersBoard board = CheckersBoard({ ROWS ,COLUMNS });

protected:
	void drawTable(class Application* _application) override;

private:


	void drawTokens(Application* _application);
	void dropTokenAnimation(Application* _application);
	void playAnimation(Application* _application);

	CheckersPawn* selected_pawn;
};

