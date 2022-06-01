#include "Button.h"

void Button::click(Application* _application) const
{
	_application->State = changeState;
	std::cout << "Click!" << std::endl;
}