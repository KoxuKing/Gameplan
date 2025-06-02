#include "UiInput.h"

UiInput::UiInput()
{
    selected = false;
    x = 0;
    y = 0;
}

bool UiInput::isSelected(Application* _application)
{
    //sf::RectangleShape rect(size);
    //// set the shape color to green
    //rect.setPosition(x, y);
    // get the bounding box of the entity

    // check collision with a point
    if (boundingBox.contains(_application->mouse.pos))
    {
        if (selected == false)
            playSound(_application->volume);

        color = sf::Color::Red;
        selected = true;
        return selected;
    }
    else
    {
        color = originalColor;
        selected = false;
        return selected;
    }
    
}

void UiInput::playSound(float &_volume)
{
    if (!soundbuffer.loadFromFile("Audio/select_audio.wav"))
        std::cout << "Couldn't find the audiofile " << std::endl;
    else
    {
        sound.setBuffer(soundbuffer);
        sound.setVolume(_volume);
        sound.play();
    }
}

void UiInput::setTexture(std::string _texturePath)
{
    
    texture.loadFromFile(_texturePath);
    texture.setRepeated(true);
    rect.setTexture(&texture);
    originalColor = rect.getFillColor();
}

bool UiInput::isClicked(Application* _application)
{
    if (isSelected(_application) && _application->mouse.clicked_left)
        clicked = true;
    else if (!isSelected(_application) && _application->mouse.clicked_left)
        clicked = false;

    return clicked;
}

void UiInput::press(class Application* _application)
{
    ;
}

void UiInput::click(Application* _application) const
{
    if (m_callback)
        m_callback();
}

void UiInput::select()
{

}

void UiInput::draw(Application* _application)
{
    //// set the shape color to green
    rect.setFillColor(color);
    _application->window.draw(rect);
    _application->window.draw(text);
}

void UiInput::setCallback(InputCallback callback)
{
    m_callback = std::move(callback);
}

void UiInput::setText(std::string _text)        // Default _x and _y is center of the button
{
    text.setString(_text);
    text.setCharacterSize(size.y / 2);
    text.setFillColor(textColor);
    textFont.loadFromFile("Fonts/testiFontti.ttf");
    text.setFont(textFont);
    // Sets text to be center of the button
    text.setPosition((size.x - text.getGlobalBounds().width) / 2 + x, (size.y - text.getLocalBounds().height) / 2 + y);
}