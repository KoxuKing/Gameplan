#pragma once
#include "UiInput.h"
class Button : public UiInput
{
public:
	Button(int _x, int _y, int _width, int _height)
	{
		x = _x;
		y = _y;
		width = _width;
		height = _height;
	}
};

