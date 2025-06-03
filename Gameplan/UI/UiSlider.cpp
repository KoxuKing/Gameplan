#include "../application.h"
#include "UiSlider.h"

Slider::Slider(float _x, float _y, int _width)
{
    circle.setRadius(radius);
    x = _x;
    y = _y;
    max_pos = _x + _width;
    min_pos = _x;
    slider_pos.x = (max_pos - x) / 10;
    size = sf::Vector2f(_width, 20);
    rect.setSize((sf::Vector2f(size.x, 5)));
    rect.setFillColor(color); // TEST
    rect.setPosition(x, y);

    // get the bounding box of the entity
    boundingBox = rect.getGlobalBounds();
}

bool Slider::isSelected(Application* _application)
{
    //// set the shape color to green

    
    // check collision with a point
    if (boundingBox.contains(_application->mouse.pos))
    {
        color = sf::Color::Red;
        return true;
    }
    else if(wasSelected)
        return true;
    else
    {
        color = sf::Color::Green;
        return false;
    }

}

void Slider::press(Application* _application)
{
    slider_pos.x = _application->mouse.pos.x - x;
    if (x + slider_pos.x >= max_pos)
        slider_pos.x = max_pos - x;
    if (x + slider_pos.x < min_pos)
        slider_pos.x = min_pos-x;
    
    scaleParameter();
}

void Slider::setText(std::string _text)
{
    main_text = _text;
    text.setString(main_text + std::to_string(int((slider_pos.x / size.x) * 100)) + " %");
    text.setCharacterSize(size.y / 2);
    text.setFillColor(textColor);
    textFont.loadFromFile("Fonts/testiFontti.ttf");
    text.setFont(textFont);
    text.setOutlineColor(sf::Color::Red);

    // Sets text to be center of the button
    text.setPosition((size.x - text.getGlobalBounds().width) / 2 + x + -75, (size.y - text.getLocalBounds().height) / 2 + y + -25);
}

void Slider::draw(Application* _application)
{

    _application->window.draw(rect);
    //// set the shape color to green
    circle.setFillColor(color); // TEST
    circle.setPosition(x + slider_pos.x - int(radius/2), y - int(radius / 2)-2);
    _application->window.draw(circle);
    updateText();
    _application->window.draw(text);
}

void Slider::updateText()
{
    text.setString(main_text + std::to_string(int((slider_pos.x / size.x) * 100)) + " %");
}

void Slider::scaleParameter()
{
    editableParameter[0] = max_value * (slider_pos.x / size.x);
}