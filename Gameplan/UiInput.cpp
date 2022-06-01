#include "UiInput.h"
#include "application.h"

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

void UiInput::click() const
{
    std::cout << "Click!" << std::endl;
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
}

void UiInput::setText(std::string& text, int x, int y)
{
}
