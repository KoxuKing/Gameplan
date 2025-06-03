#pragma once
#include "CheckersBoardSlot.h"
#include "CheckersPlayer.h"
#include <memory>

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
						slots[r][c] = BoardSlot(sf::Color::Black, std::unique_ptr<CheckersPawn>(new CheckersPawn(sf::Color::Red, { c,r })));

					else
						slots[r][c] = BoardSlot(sf::Color::Black, std::unique_ptr<CheckersPawn>(new CheckersPawn(sf::Color::Yellow, { c,r })));
				}
			}
		}
	}

	bool canPawnEat(CheckersPawn* _selected_pawn, CheckersPlayer* player);

	bool MoveSelectedPawnToSquare(std::shared_ptr<CheckersPawn> selected_pawn, CheckersPlayer* player, sf::Vector2i new_square);

	void DrawBoard(Application* _application);

	void DrawPawns(Application* _application);

	void DrawPossibleMoves(Application* _application, BoardSlot& selected_slot);

	std::vector<sf::Vector2i> getDiagonalMoves(CheckersPawn* selectedPawn, CheckersPlayer* player, bool can_palyer_eat = false);

	bool isSlotValid(sf::Vector2i slot);

	int getColumn(int _mousePosX) const;
	int getRow(int _mousePosY) const;

	std::vector<std::vector<BoardSlot>> slots;

private:

	bool eatPawnsBetweenSlots(sf::Vector2i start_square, sf::Vector2i new_square);

	sf::Vector2i size;

	const float BORDER_THICKNESS = 5;
	float slot_height = 0;
	float slot_width = 0;
	const float X_OFFSET = 100;
	const float Y_OFFSET = 100;

};