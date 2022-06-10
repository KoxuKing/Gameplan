#pragma once
#include "UiInput.h"

class Slider : public UiInput
{
public:
	Slider(int _x, int _y, int _width)
	{
		x = _x;
		y = _y;
		max_pos = _x + _width;
		min_pos = _x;
		size = sf::Vector2f(_width, 0);
	}

	virtual bool isSelected(class Application* _application);
	virtual void Press(class Application* _application);

	virtual void draw(class Application* _application);

	int radius = 10;
private:
	int max_pos;
	int min_pos;
	sf::Vector2f slider_pos = sf::Vector2f(0,0);
};

