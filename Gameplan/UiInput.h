#pragma once

#include <iostream>

class UiInput
{
public:
	UiInput() {};

	virtual bool isSelected() const;
	virtual bool isClicked() const;

	virtual void click() const;
	virtual void select();

	void setText(std::string &text, int x, int y);
protected:
	int width;
	int height;
	int x;
	int y;

	// std::string path_to_buttontexture;
	// std::string path_to_buttonselectedtexture;

private:
};

