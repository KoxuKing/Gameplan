#include "Button.h"

Button::Button(int _x, int _y, float _width, float _height)
{
	x = _x;
	y = _y;
	//changeState = -1;
	size = sf::Vector2f(_width, _height);
	
	rect.setSize(size);
	
	rect.setPosition(x, y);
	originalColor = rect.getFillColor();
	boundingBox = rect.getGlobalBounds();
}

void Button::click(Application* _application) const
{
	if (m_callback)
		m_callback();
}

void Button::setReturnButton(bool _boolean)
{
	isReturnButton = _boolean;
}


