#include "../application.h"
#include "CheckersTable.h"

void CheckersTable::update(class Player* _player, class Application* _application)
{
	drawTable(_application);
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
	sf::RectangleShape rectangle;
	sf::Color white(255, 255, 255);
	sf::Color black(0, 0, 0);

	float t = 5;
	float x_offset = 100;
	float y_offset = 100;
	float rect_width = (_application->window_width - x_offset *2) / COLUMNS;
	float rect_height = (_application->window_height - y_offset *2) / ROWS;
	
	

	rectangle.setSize(sf::Vector2f(rect_width, rect_height));
	rectangle.setOutlineColor(sf::Color::Black);
	rectangle.setOutlineThickness(t);
	
	for (int r = 0; r < ROWS; r++) {
		for (int c = 0; c < COLUMNS; c++) {
			rectangle.setPosition({ x_offset + static_cast<float>(rect_width * c), y_offset + static_cast<float>(rect_height * r) });
			
			if (board[r][c] == 0)
			{
				rectangle.setFillColor(white);
			}
			else
			{
				rectangle.setFillColor(black);
			}
			_application->window.draw(rectangle);
		}
	}
}
