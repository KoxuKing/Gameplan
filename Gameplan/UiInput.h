#pragma once
#include <iostream>
#include "application.h"

class UiInput
{
public:
	UiInput() {};

	virtual bool isSelected(class Application* _application);
	virtual bool isClicked() const;

	virtual void click(Application* _application) const;
	virtual void select();

	virtual void draw(class Application* _application);

	void setText(std::string _text, int _x, int _y);


protected:
	sf::Vector2f size;
	int x;
	int y;
	sf::Color color;

	// Ehkä structi tekstille??
	sf::Text text;
	sf::Color textColor = sf::Color::Black;
	sf::Font textFont;
	unsigned int textCharacterSize;

	// for testing
	// std::string path_to_buttontexture;
	// std::string path_to_buttonselectedtexture;
};

