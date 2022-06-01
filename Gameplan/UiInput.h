#pragma once
#include <iostream>
#include "application.h"

class UiInput
{
public:
	UiInput() {};

	virtual bool isSelected() const;
	virtual bool isClicked() const;

	virtual void click() const;
	virtual void select();

	virtual void draw(class Application* _application);

	void setText(std::string &text, int x, int y);
protected:
	sf::Vector2f size;
	int x;
	int y;

	// std::string path_to_buttontexture;
	// std::string path_to_buttonselectedtexture;

private:
};

