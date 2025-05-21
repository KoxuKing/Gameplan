#include "CheckersBoard.h"

void CheckersBoard::getDiagonalMoves(CheckersPawn& selectedPawn, CheckersPlayer* player, bool can_palyer_eat)
{
	std::vector<sf::Vector2i> possible_moves;
	possible_moves.clear();
	sf::Vector2i diagonal_1;
	sf::Vector2i diagonal_2;

	// Red pawns
	if (selectedPawn.color == sf::Color::Red && sf::Color::Red == player->color)
	{
		// down left
		diagonal_1 = { selectedPawn.board_slot.x - 1, selectedPawn.board_slot.y + 1 };
		diagonal_2 = { selectedPawn.board_slot.x - 2, selectedPawn.board_slot.y + 2 };
		if (diagonal_1.x >= 0 && diagonal_1.y < size.x) // is possibleMove?
		{
			if (slots[diagonal_1.y][diagonal_1.x].hasPawn && slots[diagonal_1.y][diagonal_1.x].pawn.color != selectedPawn.color) // ! Does Slot Have pawn
			{
				if (diagonal_2.x >= 0 && diagonal_2.y < size.x && !slots[diagonal_2.y][diagonal_2.x].hasPawn) // is eating possibleMove?
					possible_moves.push_back(diagonal_2);
			}
			else if (!slots[diagonal_1.y][diagonal_1.x].hasPawn && !can_palyer_eat) // No pawn on slot
				possible_moves.push_back(diagonal_1);
		}

		// down right
		diagonal_1 = { selectedPawn.board_slot.x + 1, selectedPawn.board_slot.y + 1 };
		diagonal_2 = { selectedPawn.board_slot.x + 2, selectedPawn.board_slot.y + 2 };
		if (diagonal_1.x < size.y && diagonal_1.y < size.x) // is possibleMove?
		{
			if (slots[diagonal_1.y][diagonal_1.x].hasPawn && slots[diagonal_1.y][diagonal_1.x].pawn.color != selectedPawn.color) // ! Does Slot Have pawn
			{
				if (diagonal_2.x < size.y && diagonal_2.y < size.x && !slots[diagonal_2.y][diagonal_2.x].hasPawn) // is eating possibleMove?
					possible_moves.push_back(diagonal_2);
			}
			else if (!slots[diagonal_1.y][diagonal_1.x].hasPawn && !can_palyer_eat) // No pawn on slot
				possible_moves.push_back(diagonal_1);
		}
	}
	else if (selectedPawn.color == sf::Color::Yellow && sf::Color::Yellow == player->color) // Yellow pawns
	{
		// up left
		diagonal_1 = { selectedPawn.board_slot.x - 1, selectedPawn.board_slot.y - 1 };
		diagonal_2 = { selectedPawn.board_slot.x - 2, selectedPawn.board_slot.y - 2 };
		if (diagonal_1.x >= 0 && diagonal_1.y >= 0) // is possibleMove?
		{
			if (slots[diagonal_1.y][diagonal_1.x].hasPawn && slots[diagonal_1.y][diagonal_1.x].pawn.color != selectedPawn.color) // ! Does Slot Have pawn
			{
				if (diagonal_2.x >= 0 && diagonal_2.y >= 0 && !slots[diagonal_2.y][diagonal_2.x].hasPawn) // is eating possibleMove?
					possible_moves.push_back(diagonal_2);
			}
			else if (!slots[diagonal_1.y][diagonal_1.x].hasPawn && !can_palyer_eat) // No pawn on slot
				possible_moves.push_back(diagonal_1);
		}


		// up right
		diagonal_1 = { selectedPawn.board_slot.x + 1, selectedPawn.board_slot.y - 1 };
		diagonal_2 = { selectedPawn.board_slot.x + 2, selectedPawn.board_slot.y - 2 };
		if (diagonal_1.x < size.y && diagonal_1.y >= 0) // is possibleMove?
		{
			if (slots[diagonal_1.y][diagonal_1.x].hasPawn && slots[diagonal_1.y][diagonal_1.x].pawn.color != selectedPawn.color) // ! Does Slot Have pawn
			{
				if (diagonal_2.x < size.y && diagonal_2.y >= 0 && !slots[diagonal_2.y][diagonal_2.x].hasPawn) // is eating possibleMove?
					possible_moves.push_back(diagonal_2);
			}
			else if (!slots[diagonal_1.y][diagonal_1.x].hasPawn && !can_palyer_eat) // No pawn on slot
				possible_moves.push_back(diagonal_1);
		}
	}

	selectedPawn.possible_moves = possible_moves;

}

int CheckersBoard::getColumn(int _mousePosX) const
{
	// Goes through every column
	for (int c = 0; c < size.y; c++)
	{
		if (_mousePosX > slots[0][c].position.x && _mousePosX < (slots[0][c].position.x + slot_width))
			return c;
	}

	return -1;
}


int CheckersBoard::getRow(int _mousePosY) const
{
	// Goes through every column
	for (int r = 0; r < size.x; r++)
	{
		if (_mousePosY < slots[r][0].position.y + slot_height && _mousePosY >(slots[0][r].position.y))
			return r;
	}

	return -1;
}

bool CheckersBoard::MoveSelectedPawnToSquare(CheckersPawn& selected_pawn, CheckersPlayer* player, sf::Vector2i new_square)
{
	if (selected_pawn.HasThisMove(new_square))
	{
		bool succesfulEat = eatPawnsBetweenSlots(selected_pawn.board_slot, new_square);

		// move pawn to new square
		slots[new_square.y][new_square.x].pawn = CheckersPawn(selected_pawn.color, new_square);
		slots[new_square.y][new_square.x].hasPawn = true;

		// remove old pawn and its moves
		slots[selected_pawn.board_slot.y][selected_pawn.board_slot.x].hasPawn = false;
		selected_pawn.possible_moves.clear();

		if (succesfulEat)
		{
			selected_pawn = slots[new_square.y][new_square.x].pawn;
			getDiagonalMoves(selected_pawn, player, true);
			if (selected_pawn.possible_moves.size() > 0)
				return false;
		}


		return true;
	}
	return false;

}

void CheckersBoard::DrawBoard(Application* _application)
{
	sf::RectangleShape slot;

	slot_width = (_application->window_width - X_OFFSET * 2) / size.y;
	slot_height = (_application->window_height - Y_OFFSET * 2) / size.x;

	slot.setSize(sf::Vector2f(slot_width, slot_height));
	slot.setOutlineColor(sf::Color::Black);
	slot.setOutlineThickness(BORDER_THICKNESS);

	for (int r = 0; r < size.x; r++) {
		for (int c = 0; c < size.y; c++) {

			sf::Vector2f slot_position = { X_OFFSET + static_cast<float>(slot_width * c), Y_OFFSET + static_cast<float>(slot_height * r) };

			// Draw slots
			slot.setPosition(slot_position);
			slots[r][c].position = slot_position;
			sf::Color slot_color = slots[r][c].color;
			slot.setFillColor(slot_color);
			_application->window.draw(slot);
		}
	}
}

void CheckersBoard::DrawPawns(Application* _application)
{

	sf::CircleShape pawn;

	slot_width = (_application->window_width - X_OFFSET * 2) / size.y;
	slot_height = (_application->window_height - Y_OFFSET * 2) / size.x;

	pawn.setRadius((std::min(slot_width, slot_height) - BORDER_THICKNESS) / 2);
	pawn.setOrigin({ -((slot_width - BORDER_THICKNESS - pawn.getRadius() * 2) / 2) , -((slot_height - BORDER_THICKNESS - pawn.getRadius() * 2) / 2) });
	pawn.setOutlineColor(sf::Color::Black);
	pawn.setOutlineThickness(BORDER_THICKNESS);

	for (int r = 0; r < size.x; r++) {
		for (int c = 0; c < size.y; c++) {

			sf::Vector2f slot_position = { X_OFFSET + static_cast<float>(slot_width * c), Y_OFFSET + static_cast<float>(slot_height * r) };

			//Draw pawns
			if (slots[r][c].hasPawn)
			{
				pawn.setPosition(slot_position);
				sf::Color pawn_color = slots[r][c].pawn.color;
				pawn.setFillColor(pawn_color);
				_application->window.draw(pawn);
			}
		}
	}
}

void CheckersBoard::DrawPossibleMoves(Application* _application, BoardSlot& selected_slot)
{

	sf::CircleShape pawn;

	slot_width = (_application->window_width - X_OFFSET * 2) / size.y;
	slot_height = (_application->window_height - Y_OFFSET * 2) / size.x;

	pawn.setRadius((std::min(slot_width, slot_height) - BORDER_THICKNESS) / 2);
	pawn.setOrigin({ -((slot_width - BORDER_THICKNESS - pawn.getRadius() * 2) / 2) , -((slot_height - BORDER_THICKNESS - pawn.getRadius() * 2) / 2) });
	pawn.setOutlineColor(sf::Color::Black);
	pawn.setOutlineThickness(BORDER_THICKNESS);


	if (selected_slot.hasPawn)
	{
		if (selected_slot.pawn.possible_moves.size() > 0)
		{
			for (int i = 0; i < selected_slot.pawn.possible_moves.size(); i++)
			{
				sf::Vector2i move = selected_slot.pawn.possible_moves[i];
				sf::Vector2f slot_position = { X_OFFSET + static_cast<float>(slot_width * move.x), Y_OFFSET + static_cast<float>(slot_height * move.y) };

				pawn.setPosition(slot_position);
				sf::Color pawn_color = selected_slot.pawn.color;
				pawn_color.a = 100;
				pawn.setFillColor(pawn_color);
				_application->window.draw(pawn);
			}
		}
	}
}

bool CheckersBoard::eatPawnsBetweenSlots(sf::Vector2i start_square, sf::Vector2i new_square)
{
	int distance_x = new_square.x - start_square.x;
	int distance_y = new_square.y - start_square.y;

	if (std::abs(distance_x) == 2 && std::abs(distance_y) == 2)
	{
		BoardSlot& target_slot = slots[new_square.y][new_square.x];
		BoardSlot& check_slot = slots[start_square.y + (distance_y / 2)][start_square.x + (distance_x / 2)];

		if (check_slot.hasPawn and !target_slot.hasPawn)
		{
			check_slot.hasPawn = false;
			return true;
		}
	}
	return false;
}

bool CheckersBoard::canPawnEat(CheckersPawn& _selected_pawn, CheckersPlayer* player)
{
	getDiagonalMoves(_selected_pawn, player, false);
	for (int i = 0; i < _selected_pawn.possible_moves.size(); i++)
	{
		sf::Vector2i move = _selected_pawn.possible_moves[i];
		sf::Vector2i move_normal = { (move.x - _selected_pawn.board_slot.x) / 2 , (move.y - _selected_pawn.board_slot.y) / 2 };
		if (std::abs(move.x - _selected_pawn.board_slot.x) > 1)//if (slots[move.y][move.x].hasPawn)// && !slots[move.x - move_normal.x][move.x - move_normal.y].hasPawn)
			return true;
	}
	return false;
}

bool CheckersBoard::isSlotValid(sf::Vector2i slot)
{
	return slot.x > -1 && slot.y > -1;
}