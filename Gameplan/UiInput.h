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

	void setText(std::string &text, int x, int y);

protected:
	sf::Vector2f size;
	int x;
	int y;
	sf::Color color;
	// for testing
	// std::string path_to_buttontexture;
	// std::string path_to_buttonselectedtexture;
};

