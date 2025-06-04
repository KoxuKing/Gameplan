#include "CheckersBoard.h"

CheckersBoard::CheckersBoard(sf::Vector2i size) : size(size)
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

// Helper function - kept in core file since it's used by multiple other files
bool CheckersBoard::isPositionInBounds(const sf::Vector2i& pos) const
{
    return pos.x >= 0 && pos.x < size.y && pos.y >= 0 && pos.y < size.x;
}

// Helper for drawing - kept in core file as it's used by multiple rendering methods
sf::CircleShape CheckersBoard::createPawnShape() const
{
    sf::CircleShape pawn;
    pawn.setRadius((std::min(slot_width, slot_height) - BORDER_THICKNESS) / PAWN_OUTLINE_THICKNESS);
    pawn.setOrigin({ -((slot_width - BORDER_THICKNESS - pawn.getRadius() * PAWN_OUTLINE_THICKNESS) / PAWN_OUTLINE_THICKNESS),
                    -((slot_height - BORDER_THICKNESS - pawn.getRadius() * PAWN_OUTLINE_THICKNESS) / PAWN_OUTLINE_THICKNESS) });
    pawn.setOutlineColor(sf::Color::Black);
    pawn.setOutlineThickness(BORDER_THICKNESS);
    return pawn;
}