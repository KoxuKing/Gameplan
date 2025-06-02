#pragma once
#include "UiInput.h"
class Button : public UiInput
{
public:
	Button(int _x, int _y, float _width, float _height);

	virtual void click(Application* _application) const;
	
	mutable int changeState = -1;
	std::string buttonAttribute = "";

	void setReturnButton(bool _boolean);

private:
	bool isReturnButton = false;

};

