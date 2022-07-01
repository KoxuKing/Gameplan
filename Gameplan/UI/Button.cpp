#include "Button.h"

Button::Button(int _x, int _y, float _width, float _height)
{
	x = _x;
	y = _y;
	changeState = 0;
	size = sf::Vector2f(_width, _height);
	
	rect.setSize(size);
	texture.loadFromFile("Textures/testTexture.png");
	rect.setTexture(&texture); // TEST
	rect.setPosition(x, y);
	originalColor = rect.getFillColor();
	boundingBox = rect.getGlobalBounds();
}

void Button::click(Application* _application) const
{
	_application->ui.State = changeState;
	_application->game.selectGame(buttonAttribute);
}


