#pragma once
#include "../application.h"

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

struct CheckersBoard {

public:
	CheckersBoard(sf::Vector2i size) : size(size)
	{
		slots.resize(size.x, std::vector<BoardSlot>(size.y, BoardSlot(sf::Color::White)));

		// 0 = white square, 1 = black square, 2 = black square with pawn
		for (int r = 0; r < size.x; r++)
		{
			for (int c = 0; c < size.y; c++)
			{
				if (r % 2 == 0 && c % 2 == 0)
					slots[r][c] = BoardSlot(sf::Color::White);
				else if (r % 2 != 0 && c % 2 != 0)
					slots[r][c] = BoardSlot(sf::Color::White);
				else // black or pawn
				{
					if (r > 2 && r < 5) // empty black
						slots[r][c] = BoardSlot(sf::Color::Black);

					else if (r < 3)
						slots[r][c] = BoardSlot(sf::Color::Black, new CheckersPawn(sf::Color::Red));

					else
						slots[r][c] = BoardSlot(sf::Color::Black, new CheckersPawn(sf::Color::Yellow));
				}
			}
		}
	}

	~CheckersBoard() {
		for (int r = 0; r < size.x; r++)
			for (int c = 0; c < size.y; c++)
				if (slots[r][c].pawn) delete slots[r][c].pawn;
	}

	bool MoveSelectedPawnToSquare(CheckersPawn* selected_pawn, sf::Vector2i new_square);

	void DrawBoard(Application* _application);

	void DrawPawns(Application* _application);

	void DrawPossibleMoves(Application* _application, CheckersPawn* selected_pawn);

	void getPossibleMoves(CheckersPawn* selectedPawn);

	int getColumn(int _mousePosX) const;
	int getRow(int _mousePosY) const;

	std::vector<std::vector<BoardSlot>> slots;

private:

	bool eatPawnsBetweenSlots(sf::Vector2i start_square, sf::Vector2i new_square);

	/*bool canPawnEat(CheckersPawn* selected_pawn) const
	{
		for (int i = 0; i < selected_pawn->possible_moves.size(); i++)
		{
			sf::Vector2i move = selected_pawn->possible_moves[i];
			if (slots[move.y][move.x].pawn)
				return true;
		}
		return false;
	}*/
	
	sf::Vector2i size;

	const float BORDER_THICKNESS = 5;
	float slot_height;
	float slot_width;
	const float X_OFFSET = 100;
	const float Y_OFFSET = 100;

};