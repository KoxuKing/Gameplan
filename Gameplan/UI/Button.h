#pragma once
#include "UiInput.h"
class Button : public UiInput
{
public:
	Button(int _x, int _y, float _width, float _height);

	void click(Application* _application) const override;
	
	//mutable int changeState = -1;

	void setReturnButton(bool _boolean);

private:
	bool isReturnButton = false;

};

