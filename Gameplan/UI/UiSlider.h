#pragma once
#include "UiInput.h"

class Slider : public UiInput
{
public:
	Slider(float _x, float _y, int _width);

	bool isSelected(Application* _application) override;
	void press(class Application* const _application) override;
	void draw(class Application* const _application) override;
	void setText(std::string _text) override;
	void setParameter(float& _editableParameter, float _max_value)
	{
		editableParameter = &_editableParameter;
		max_value = _max_value;
	}
	int radius = 10;

private:
	sf::CircleShape circle;

	int max_pos{};
	int min_pos{};
	float* editableParameter{};
	float max_value{};
	sf::Vector2f slider_pos = sf::Vector2f(0,0);
	sf::Text scaleText;
	void scaleParameter();
	void updateText();
	std::string main_text;
};

