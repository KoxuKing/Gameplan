#pragma once
#include "UiInput.h"
class Button : public UiInput
{
public:
	Button(int _x, int _y, int _width, int _height)
	{
		x = _x;
		y = _y;
		size = sf::Vector2f(_width, _height);
	}
	
};

