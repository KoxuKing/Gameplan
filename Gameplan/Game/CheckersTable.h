#pragma once
#include "GameTable.h"
#include <vector>
#include <memory>

struct CheckersPawn;

struct BoardSlot {
public:

	BoardSlot(sf::Color color, CheckersPawn* pawn = nullptr)
		: color(color), pawn(pawn) {}

	sf::Color color;
	CheckersPawn* pawn;
	sf::Vector2f position;

};

struct CheckersPawn {

public:
	CheckersPawn(sf::Color color) : color(color) {}

	bool HasThisMove(sf::Vector2i move)
	{
		for (int i = 0; i < possible_moves.size(); i++)
		{
			if (possible_moves[i] == move)
				return true;
		}
		return false;
	}

	sf::Color color;
	std::vector<sf::Vector2i> possible_moves;

	sf::Vector2i board_slot;
};


class CheckersTable : public GameTable
{
public:
	CheckersTable()
	{
		board.resize(ROWS, std::vector<BoardSlot>(COLUMNS, BoardSlot(sf::Color::White)));

		// 0 = white square, 1 = black square, 2 = black square with pawn
		for (int r = 0; r < ROWS; r++)
		{
			for (int c = 0; c < COLUMNS; c++)
			{
				if (r % 2 == 0 && c % 2 == 0)
					board[r][c] = BoardSlot(sf::Color::White);
				else if (r % 2 != 0 && c % 2 != 0)
					board[r][c] = BoardSlot(sf::Color::White);
				else // black or pawn
				{
					if (r > 2 && r < 5) // empty black
						board[r][c] = BoardSlot(sf::Color::Black);

					else if (r < 3)
						board[r][c] = BoardSlot(sf::Color::Black, new CheckersPawn(sf::Color::Red));

					else
						board[r][c] = BoardSlot(sf::Color::Black, new CheckersPawn(sf::Color::Yellow));
				}
			}
		}
	}

	~CheckersTable() {
		for (int r = 0; r < ROWS; r++)
			for (int c = 0; c < COLUMNS; c++)
				if (board[r][c].pawn) delete board[r][c].pawn;
	}

	void update(class Player* _player, class Application* _application) override;
	void unfocusTable() override;
	void focusTable() override;


	const int RECT_SIZE = 50;
	const int ROWS = 8;
	const int COLUMNS = 8;

	// Initialize the 2D vector board
	std::vector<std::vector<BoardSlot>> board;

protected:
	void drawTable(class Application* _application) override;

private:

	int getColumn(int _mousePosX) const;
	int getRow(int _mousePosY) const;
	void getPossibleMoves(CheckersPawn* selectedPawn);


	void drawTokens(Application* _application);
	void dropTokenAnimation(Application* _application);
	void playAnimation(Application* _application);
	float animationPos{};

	float slot_height;
	float slot_width;
	float board_x_offset = 100;
	float board_y_offset = 100;

	CheckersPawn* selected_pawn;
};

