#include "UiInput.h"

bool UiInput::isSelected(Application* _application)
{
    sf::RectangleShape rect(size);
    //// set the shape color to green
    rect.setPosition(x, y);
    // get the bounding box of the entity
    sf::FloatRect boundingBox = rect.getGlobalBounds();

    // check collision with a point
    if (boundingBox.contains(_application->mouse.pos))
    {
        color = sf::Color::Red;
        return true;
    }
    else
    {
        color = sf::Color::Green;
        return false;
    }
    
}

bool UiInput::isClicked() const
{
    
    return false;
}

void UiInput::click(Application* _application) const
{
    ;
}

void UiInput::select()
{

}

void UiInput::draw(Application* _application)
{
    sf::RectangleShape rect(size);
    //// set the shape color to green
    rect.setFillColor(color); // TEST
    rect.setPosition(x,y);
    _application->window.draw(rect);
    _application->window.draw(text);
}

void UiInput::setText(std::string _text, int _x = 0, int _y = 0)        // Default _x and _y is center of the button
{
    textCharacterSize = size.y / 2;
    text.setString(_text);
    text.setCharacterSize(textCharacterSize);
    text.setFillColor(textColor);
    textFont.loadFromFile("Fonts/testiFontti.ttf");
    text.setFont(textFont);

    // Sets text to be center of the button
    text.setPosition((size.x - text.getLocalBounds().width) / 2 + x + _x, (size.y - text.getLocalBounds().height) / 2 + y + _y);
    
    std::cout << "Pituus: " << text.getLetterSpacing() * _text.length() << std::endl;
    std::cout << "Pounds: " << (size.x - text.getLocalBounds().width) / 2 + _x << std::endl;
}