#include "UiSlider.h"

bool Slider::isSelected(Application* _application)
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
    
    scaleParam();
}

void Slider::setText(std::string _text, int _x, int _y)
{
    main_text = _text;
    textCharacterSize = size.y / 2;
    text.setString(main_text + std::to_string(int((slider_pos.x / size.x) * 100)) + " %");
    text.setCharacterSize(textCharacterSize);
    text.setFillColor(textColor);
    textFont.loadFromFile("Fonts/testiFontti.ttf");
    text.setFont(textFont);
    text.setOutlineColor(sf::Color::Red);

    // Sets text to be center of the button
    text.setPosition((size.x - text.getGlobalBounds().width) / 2 + x + _x, (size.y - text.getLocalBounds().height) / 2 + y + _y);
}

void Slider::draw(Application* _application)
{
    sf::RectangleShape rect(sf::Vector2f(size.x, 5));
    rect.setFillColor(sf::Color::Black);
    rect.setPosition(x,y);
    _application->window.draw(rect);
    sf::CircleShape circle(radius);
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

void Slider::scaleParam()
{
    editableParameter[0] = max_value * (slider_pos.x / size.x);
}