#pragma once
#include "../application.h"
#include "CheckersPlayer.h"

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

struct BoardSlot {
public:

	BoardSlot(sf::Color color, bool hasPawn,CheckersPawn pawn = CheckersPawn(sf::Color::Black))
		: color(color), hasPawn(hasPawn), pawn(pawn) {}

	sf::Color color;
	CheckersPawn pawn;
	sf::Vector2f position;

	bool hasPawn = false;

};



struct CheckersBoard {

public:
	CheckersBoard(sf::Vector2i size) : size(size)
	{
		slots.resize(size.x, std::vector<BoardSlot>(size.y, BoardSlot(sf::Color::White, false)));

		// 0 = white square, 1 = black square, 2 = black square with pawn
		for (int r = 0; r < size.x; r++)
		{
			for (int c = 0; c < size.y; c++)
			{
				if (r % 2 == 0 && c % 2 == 0)
					slots[r][c] = BoardSlot(sf::Color::White, false);
				else if (r % 2 != 0 && c % 2 != 0)
					slots[r][c] = BoardSlot(sf::Color::White, false);
				else // black or pawn
				{
					if (r > 2 && r < 5) // empty black
						slots[r][c] = BoardSlot(sf::Color::Black, false);

					else if (r < 3)
						slots[r][c] = BoardSlot(sf::Color::Black, true, CheckersPawn(sf::Color::Red));

					else
						slots[r][c] = BoardSlot(sf::Color::Black, true, CheckersPawn(sf::Color::Yellow));
				}
			}
		}
	}

	bool canPawnEat(CheckersPawn& selected_pawn, CheckersPlayer* player)
	{
		getDiagonalMoves(selected_pawn, player);
		for (int i = 0; i < selected_pawn.possible_moves.size(); i++)
		{
			sf::Vector2i move = selected_pawn.possible_moves[i];
			sf::Vector2i move_normal = { (move.x - selected_pawn.board_slot.x)/2 , (move.y - selected_pawn.board_slot.y)/2 };
			std::cout << move.x << std::endl;
			std::cout << move.y << std::endl;
			std::cout << move.x - move_normal.x << std::endl;
			std::cout << move.y - move_normal.y << std::endl;
			if (std::abs(move.x - selected_pawn.board_slot.x) > 1)//if (slots[move.y][move.x].hasPawn)// && !slots[move.x - move_normal.x][move.x - move_normal.y].hasPawn)
				return true;
		}
		return false;
	}

	bool MoveSelectedPawnToSquare(CheckersPawn& selected_pawn, CheckersPlayer* player, sf::Vector2i new_square);

	void DrawBoard(Application* _application);

	void DrawPawns(Application* _application);

	void DrawPossibleMoves(Application* _application, BoardSlot& selected_slot);

	void getDiagonalMoves(CheckersPawn& selectedPawn, CheckersPlayer* player, bool can_palyer_eat = false);

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