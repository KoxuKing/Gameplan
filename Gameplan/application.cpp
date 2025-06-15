#include "application.h"
#include <iostream>
#include "SFML/Audio.hpp"

Application::Application()
{
    // Init window
    window.create(sf::VideoMode(window_width, window_height), "GamePlatform");
    window.setVerticalSyncEnabled(true);
    window.setFramerateLimit(fps);
}

int Application::run()
{
    // TEST THEME// LATER CREATE AUDIO CLASS?
    sf::Music theme;
    if (!theme.openFromFile("Audio/opmusiikki.wav"))
        std::cout << "Couldn't find the audiofile " << std::endl;
    else
    {
        theme.play();
        theme.setLoop(true);
    }

    while(window.isOpen())
    {
        timePassed = clock.getElapsedTime();

        //Set theme music volume
        theme.setVolume(volume/10);

        // check all the window's events that were triggered since the last iteration of the loop
        sf::Event ev;
        // Process events
        while (window.pollEvent(ev)) {
            event = ev;
            updateUserInputs(event);
        }
        
        // clear the window with black color
        window.clear();
        
        // Game logic uses click states here
        switch (State)
        {
        case ApplicationState::GAME:
            game.update();  // Has access to clicks
            break;
        case ApplicationState::SHUTDOWN:
            ui.shutdown();
            game.shutdown();
            shutdown();
            break;
        default:
            break;
        }
        
        ui.update();

        // Reset click flags after game logic has used them
        resetClickFlags();

        // end the current frame
        window.display();
    }
    return 0;
}

int Application::shutdown()
{
    window.close();
    return 0;
}

void Application::updateUserInputs(sf::Event &_event)
{
    // "close requested" event: we close the window
    if (_event.type == sf::Event::Closed)
        window.close();

    if (_event.text.unicode < 128 && _event.type == sf::Event::TextEntered)
    {
        if (startTime == 0)
            startTime = timePassed.asSeconds();
        keyboard.timeHolded = timePassed.asSeconds() - startTime;

        if (_event.text.unicode != keyboard.keyUnicode)
            keyboard.timeHolded = 0;

        keyboard.isKeyPressed = true;
        keyboard.isKeyReleased = false;

        keyboard.pressedKey = (char)(_event.text.unicode);
        keyboard.keyUnicode = _event.text.unicode;
    }
    if (_event.type == sf::Event::KeyReleased && keyboard.isKeyPressed)
    { 
        keyboard.timeHolded = 0;
        startTime = 0;
        keyboard.isKeyReleased = true;
        keyboard.isKeyPressed = false;
    }
        
    // MOUSE CONTROL - Updated approach
    // Handle press/release events
    if (_event.type == sf::Event::MouseButtonPressed)
    {
        if (_event.mouseButton.button == sf::Mouse::Left)
            mouse.pressed_left = true;
        if (_event.mouseButton.button == sf::Mouse::Right)
            mouse.pressed_right = true;
    }
    else if (_event.type == sf::Event::MouseButtonReleased)
    {
        if (_event.mouseButton.button == sf::Mouse::Left)
        {
            if (mouse.pressed_left) {  // Ensure press was detected
                mouse.clicked_left = true;  // Set click flag
            }
            mouse.pressed_left = false;
        }
        if (_event.mouseButton.button == sf::Mouse::Right)
        {
            if (mouse.pressed_right) {  // Ensure press was detected
                mouse.clicked_right = true;  // Set click flag
            }
            mouse.pressed_right = false;
        }
    }
    
    if (_event.type == sf::Event::MouseMoved)
    {
        mouse.pos = sf::Vector2f(_event.mouseMove.x, _event.mouseMove.y);
    }
}

void Application::resetClickFlags()
{
    // Reset click flags after the game logic has had a chance to use them
    mouse.clicked_left = false;
    mouse.clicked_right = false;
}
