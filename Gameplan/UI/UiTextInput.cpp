#include "UiTextInput.h"

UiTextInput::UiTextInput(int _x, int _y, int _maxChar)
{
	x = _x;
	y = _y;
	maxChar = _maxChar;
	texturePath = "Textures/testTexture.png";
	setTexture(texturePath);
	rect.setPosition(x, y);
	size = sf::Vector2f(_maxChar * 20, 50);
	rect.setSize(size);
	textColor = sf::Color::Black;
	boundingBox = rect.getGlobalBounds();
	originalColor = rect.getFillColor();


}

void UiTextInput::draw(Application* _application)
{
	
	if (isClicked(_application))
	{
		updateInput(_application);
		rect.setFillColor(sf::Color(105, 105, 105, 255));
	}
	else
		rect.setFillColor(originalColor);

	if (inputText == "")
	{
		textColor = sf::Color(0, 0, 0, 100);
		setText(placeholder);
	}
	else
	{
		textColor = sf::Color::Black;
		setText(inputText);
	}
	_application->window.draw(rect);
	_application->window.draw(text);

}

void UiTextInput::setPlaceholder(std::string _placeholder)
{
	placeholder = _placeholder;
}

void UiTextInput::updateInput(Application* _application)
{
	std::cout << _application->keyboard.timeHolded << std::endl;

	if (isFirstChar && _application->keyboard.isKeyPressed || (_application->keyboard.timeHolded > 0.6 && _application->timePassed.asSeconds() - timePassedFromLastInput > 0.03))
	{
		isFirstChar = false;
		timePassedFromLastInput = _application->timePassed.asSeconds();
		if (_application->keyboard.keyUnicode == 8 && charAmount > 0) // 8 = backspace
		{
			charAmount--;
			inputTextVector.pop_back();
		}
		else if (inputText.size() < maxChar && _application->keyboard.keyUnicode != 8)
		{
			inputTextVector.push_back(_application->keyboard.pressedKey);
			charAmount++;
		}
		charVectorToString();
	}
	else if (_application->keyboard.timeHolded == 0)
		isFirstChar = true;
}

void UiTextInput::charVectorToString()
{
	inputText = "";
	for (char character : inputTextVector)
	{
		inputText += character;
	}
}
