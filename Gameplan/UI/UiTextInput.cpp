#include "../application.h"
#include "UiTextInput.h"

UiTextInput::UiTextInput(float _x, float _y, unsigned int _maxChar)
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

	if (text.getLocalBounds().width + text.getPosition().x + size.x / 10.0f > rect.getLocalBounds().width + rect.getPosition().x)
	{
		rect.setPosition(sf::Vector2f(rect.getPosition().x - 6.0f, rect.getPosition().y));
		rect.setSize(sf::Vector2f(rect.getLocalBounds().width + 12.0f, rect.getLocalBounds().height)); // TESTI!!
	}
	else if (text.getLocalBounds().width + text.getPosition().x + size.x / 10.0f < size.x + rect.getPosition().x)
	{
		rect.setPosition(sf::Vector2f(x, y));
		rect.setSize(size);
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
		textColor = sf::Color::Black;
		setText(inputText);
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
