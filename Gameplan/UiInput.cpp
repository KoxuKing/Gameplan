#include "UiInput.h"

bool UiInput::isSelected() const
{
    return false;
}

bool UiInput::isClicked() const
{
    return false;
}

void UiInput::click() const
{
}

void UiInput::select()
{
}

void UiInput::draw(Application* _application)
{
    sf::RectangleShape rect(size);
    //// set the shape color to green
    rect.setFillColor(sf::Color(100, 250, 50)); // TEST
    rect.setPosition(x,y);
    _application->window.draw(rect);
}

void UiInput::setText(std::string& text, int x, int y)
{
}
