#include "../application.h"
#include "CheckersTable.h"

void CheckersTable::update(class Player* _player, class Application* _application)
{
	if (_application->game.isGameOn)
	{
		if (_application->mouse.clicked_left)
		{
			int column = getColumn(_application->mouse.pos.x);
			int row = getRow(_application->mouse.pos.y);

			if (board[row][column].pawn != nullptr)
			{
				selected_pawn = board[row][column].pawn;
				selected_pawn->board_slot = { column, row };
				getPossibleMoves(selected_pawn);
			}
			else if (selected_pawn)
			{
				if (selected_pawn->HasThisMove({ column, row }))
				{
					board[row][column].pawn = new CheckersPawn(selected_pawn->color);
					board[row][column].pawn->board_slot = { column, row };
					board[selected_pawn->board_slot.y][selected_pawn->board_slot.x].pawn = nullptr;
					delete selected_pawn;
					selected_pawn = nullptr;
				}
				else selected_pawn->possible_moves.clear();
			}
		}
	}

	drawTable(_application);
}

void CheckersTable::getPossibleMoves(CheckersPawn* selectedPawn)
{
	std::vector<sf::Vector2i> possible_moves;

	sf::Vector2i diagonal;

	// Red pawns
	if (selectedPawn->color == sf::Color::Red)
	{
		//std::cout << "red" << std::endl;
		// down left
		diagonal = { selectedPawn->board_slot.x - 1, selectedPawn->board_slot.y + 1 };
		if (diagonal.x >= 0 && diagonal.y < ROWS && board[diagonal.y][diagonal.x].pawn == nullptr)
		{
			//std::cout << "left" << std::endl;
			possible_moves.push_back(diagonal);
		}
			
		// down right
		diagonal = { selectedPawn->board_slot.x + 1, selectedPawn->board_slot.y + 1 };
		std::cout << diagonal.x << std::endl;
		std::cout << diagonal.y << std::endl;
		if (diagonal.x < COLUMNS && diagonal.y < ROWS && board[diagonal.y][diagonal.x].pawn == nullptr)
		{
			//std::cout << "right" << std::endl;
			possible_moves.push_back(diagonal);
		}
			
	}
	else // Yellow pawns
	{
		// up left
		diagonal = { selectedPawn->board_slot.x - 1, selectedPawn->board_slot.y - 1 };
		std::cout << diagonal.x << std::endl;
		std::cout << diagonal.y << std::endl;
		if (diagonal.x >= 0 && diagonal.y >= 0 && board[diagonal.y][diagonal.x].pawn == nullptr)
		{
			//std::cout << "left" << std::endl;
			possible_moves.push_back(diagonal);
		}

		// up right
		diagonal = { selectedPawn->board_slot.x + 1, selectedPawn->board_slot.y - 1 };
		if (diagonal.x < COLUMNS && diagonal.y >= 0 && board[diagonal.y][diagonal.x].pawn == nullptr)
		{
			std::cout << "right" << std::endl;
			possible_moves.push_back(diagonal);
		}
	}

	selectedPawn->possible_moves = possible_moves;

}

int CheckersTable::getColumn(int _mousePosX) const
{
	// Goes through every column
	for (int c = 0; c < COLUMNS; c++)
	{
		if (_mousePosX > board[0][c].position.x && _mousePosX < (board[0][c].position.x + slot_width))
			return c;
	}

	return -1;
}


int CheckersTable::getRow(int _mousePosY) const
{
	// Goes through every column
	for (int r = 0; r < ROWS; r++)
	{
		if (_mousePosY < board[r][0].position.y + slot_height && _mousePosY > (board[0][r].position.y))
			return r;
	}

	return -1;
}

void CheckersTable::unfocusTable()
{
	;
}
void CheckersTable::focusTable()
{
	;
}

void CheckersTable::drawTable(class Application* _application)
{
	sf::RectangleShape slot;
	sf::CircleShape pawn;


	float t = 5;

	slot_width = (_application->window_width - board_x_offset *2) / COLUMNS;
	slot_height = (_application->window_height - board_y_offset *2) / ROWS;
	
	slot.setSize(sf::Vector2f(slot_width, slot_height));
	slot.setOutlineColor(sf::Color::Black);
	slot.setOutlineThickness(t);

	pawn.setRadius((std::min(slot_width, slot_height) - t)/2);
	pawn.setOrigin({ -((slot_width - t - pawn.getRadius()*2)/2) , -((slot_height - t - pawn.getRadius() * 2)/2) });
	pawn.setOutlineColor(sf::Color::Black);
	pawn.setOutlineThickness(t);
	
	for (int r = 0; r < ROWS; r++) {
		for (int c = 0; c < COLUMNS; c++) {

			sf::Vector2f slot_position = { board_x_offset + static_cast<float>(slot_width * c), board_y_offset + static_cast<float>(slot_height * r) };
			
			// Draw slots
			slot.setPosition(slot_position);
			board[r][c].position = slot_position;
			sf::Color slot_color = board[r][c].color;
			slot.setFillColor(slot_color);
			_application->window.draw(slot);

			//Draw pawns
			if (board[r][c].pawn)
			{
				pawn.setPosition(slot_position);
				sf::Color pawn_color = board[r][c].pawn->color;
				pawn.setFillColor(pawn_color);
				_application->window.draw(pawn);
			}	
		}
	}
	
	if (selected_pawn)
	{
		if (selected_pawn->possible_moves.size() > 0)
		{
			for (int i = 0; i < selected_pawn->possible_moves.size(); i++)
			{
				sf::Vector2i move = selected_pawn->possible_moves[i];
				sf::Vector2f slot_position = {board_x_offset + static_cast<float>(slot_width * move.x), board_y_offset + static_cast<float>(slot_height * move.y)};

				pawn.setPosition(slot_position);
				sf::Color pawn_color = selected_pawn->color;
				pawn_color.a = 100;
				pawn.setFillColor(pawn_color);
				_application->window.draw(pawn);
			}
		}
	}
}