#include "Button.h"



void Button::click(Application* _application) const
{
	_application->ui.State = changeState;
}


