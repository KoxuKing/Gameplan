#include "Checkers.h"

void CheckersBoard::getPossibleMoves(CheckersPawn* selectedPawn)
{
	std::vector<sf::Vector2i> possible_moves;

	sf::Vector2i diagonal;

	// Red pawns
	if (selectedPawn->color == sf::Color::Red)
	{
		//std::cout << "red" << std::endl;
		// down left
		for (int i = 1; i < 3; i++)
		{
			diagonal = { selectedPawn->board_slot.x - i, selectedPawn->board_slot.y + i };
			if (diagonal.x >= 0 && diagonal.y < size.x)
			{
				if (slots[diagonal.y][diagonal.x].pawn == nullptr)
				{
					possible_moves.push_back(diagonal);
					break;
				}
			}
		}

		// down right
		for (int i = 1; i < 3; i++)
		{
			diagonal = { selectedPawn->board_slot.x + i, selectedPawn->board_slot.y + i };
			if (diagonal.x < size.y && diagonal.y < size.x)
			{
				if (slots[diagonal.y][diagonal.x].pawn == nullptr)
				{
					possible_moves.push_back(diagonal);
					break;
				}
			}	
		}
	}
	else // Yellow pawns
	{
		// up left
		for (int i = 1; i < 3; i++)
		{
			diagonal = { selectedPawn->board_slot.x - i, selectedPawn->board_slot.y - i };
			if (diagonal.x >= 0 && diagonal.y >= 0)
			{
				if (slots[diagonal.y][diagonal.x].pawn == nullptr)
				{
					possible_moves.push_back(diagonal);
					break;
				}
			}
		}
		

		// up right
		for (int i = 1; i < 3; i++)
		{
			diagonal = { selectedPawn->board_slot.x + i, selectedPawn->board_slot.y - i };
			if (diagonal.x < size.y && diagonal.y >= 0)
			{
				if (slots[diagonal.y][diagonal.x].pawn == nullptr)
				{
					possible_moves.push_back(diagonal);
					break;
				}
				
			}
		}
		
	}

	selectedPawn->possible_moves = possible_moves;

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

bool CheckersBoard::MoveSelectedPawnToSquare(CheckersPawn* selected_pawn, sf::Vector2i new_square)
{
	if (selected_pawn->HasThisMove(new_square))
	{
		eatPawnsBetweenSlots(selected_pawn->board_slot, new_square);

		slots[new_square.y][new_square.x].pawn = new CheckersPawn(selected_pawn->color);
		slots[new_square.y][new_square.x].pawn->board_slot = new_square;
		slots[selected_pawn->board_slot.y][selected_pawn->board_slot.x].pawn = nullptr;
		delete selected_pawn;
		selected_pawn = nullptr;
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
			if (slots[r][c].pawn)
			{
				pawn.setPosition(slot_position);
				sf::Color pawn_color = slots[r][c].pawn->color;
				pawn.setFillColor(pawn_color);
				_application->window.draw(pawn);
			}
		}
	}
}

void CheckersBoard::DrawPossibleMoves(Application* _application, CheckersPawn* selected_pawn)
{

	sf::CircleShape pawn;

	slot_width = (_application->window_width - X_OFFSET * 2) / size.y;
	slot_height = (_application->window_height - Y_OFFSET * 2) / size.x;

	pawn.setRadius((std::min(slot_width, slot_height) - BORDER_THICKNESS) / 2);
	pawn.setOrigin({ -((slot_width - BORDER_THICKNESS - pawn.getRadius() * 2) / 2) , -((slot_height - BORDER_THICKNESS - pawn.getRadius() * 2) / 2) });
	pawn.setOutlineColor(sf::Color::Black);
	pawn.setOutlineThickness(BORDER_THICKNESS);


	if (selected_pawn)
	{
		if (selected_pawn->possible_moves.size() > 0)
		{
			for (int i = 0; i < selected_pawn->possible_moves.size(); i++)
			{
				sf::Vector2i move = selected_pawn->possible_moves[i];
				sf::Vector2f slot_position = { X_OFFSET + static_cast<float>(slot_width * move.x), Y_OFFSET + static_cast<float>(slot_height * move.y) };

				pawn.setPosition(slot_position);
				sf::Color pawn_color = selected_pawn->color;
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

		if (check_slot.pawn != nullptr and target_slot.pawn == nullptr)
		{
			delete check_slot.pawn;
			check_slot.pawn = nullptr;
			return true;
		}
	}
	return false;
}