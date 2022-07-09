#include "Button.h"

Button::Button(int _x, int _y, float _width, float _height)
{
	x = _x;
	y = _y;
	changeState = 0;
	size = sf::Vector2f(_width, _height);
	
	rect.setSize(size);
	texturePath = "Textures/testTexture.png";
	setTexture(texturePath);
	rect.setPosition(x, y);
	originalColor = rect.getFillColor();
	boundingBox = rect.getGlobalBounds();
}

void Button::click(Application* _application) const
{
	if(changeState != -1)
		_application->ui.State = changeState;
	if(buttonAttribute != "")
		_application->game.selectGame(buttonAttribute);
	if (callBack != nullptr)
		callBack;
}

template <typename T>
void Button::addCallBack(void (T::* _callBack)(sf::IpAddress, int))
{
	callBack = _callBack;
}


