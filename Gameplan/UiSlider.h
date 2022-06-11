#pragma once
#include "UiInput.h"

class Slider : public UiInput
{
public:
	Slider(int _x, int _y, int _width, float *_editableParameter, float _max_value)
	{
		x = _x;
		y = _y;
		max_pos = _x + _width;
		min_pos = _x;
		slider_pos.x = (max_pos-x) / 2;
		size = sf::Vector2f(_width, 20);
		editableParameter = _editableParameter;
		max_value = _max_value;
	}

	virtual bool isSelected(class Application* _application);
	virtual void press(class Application* _application);
	virtual void draw(class Application* _application);
	virtual void setText(std::string _text, int _x = 0, int _y = 0);
	int radius = 10;

private:
	int max_pos;
	int min_pos;
	float* editableParameter;
	float max_value;
	sf::Vector2f slider_pos = sf::Vector2f(0,0);
	sf::Text scaleText;
	void scaleParam();
	void updateText();
	std::string main_text;
};

