#include "UiSlider.h"

bool Slider::isSelected(Application* _application)
{
    sf::CircleShape circle(10);
    //// set the shape color to green
    circle.setPosition(x + slider_pos.x - int(radius / 2), y);
    // get the bounding box of the entity
    sf::FloatRect boundingBox = circle.getGlobalBounds();

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

void Slider::Press(Application* _application)
{
    slider_pos.x = _application->mouse.pos.x - x;
    if (x >= max_pos)
        slider_pos.x = max_pos;
    if (x < min_pos)
        slider_pos.x = min_pos;
    
}

void Slider::draw(Application* _application)
{
    sf::RectangleShape rect(sf::Vector2f(size.x, 5));
    rect.setFillColor(sf::Color::Black);
    rect.setPosition(x,y-(size.y/2));
    _application->window.draw(rect);
    sf::CircleShape circle(radius);
    //// set the shape color to green
    circle.setFillColor(color); // TEST
    circle.setPosition(x + slider_pos.x - int(radius/2), y);
    _application->window.draw(circle);
    //_application->window.draw(text);
}