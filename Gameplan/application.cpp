#include "application.h"
#include <iostream>

Application::Application()
{
    // Init window
    window.create(sf::VideoMode(window_width, window_height), "GamePlatform");
    window.setVerticalSyncEnabled(true);
    window.setFramerateLimit(fps);
}

int Application::run()
{
    while(window.isOpen())
    {
        // check all the window's events that were triggered since the last iteration of the loop
        sf::Event event;
        while (window.pollEvent(event))
        {
            updateUserInputs(event);
        }

        // clear the window with black color
        window.clear();
        
        switch (State)
        {
        case ApplicationState::STATE_GAME:
            game.update();
            break;
        case ApplicationState::STATE_UI:
            ui.update();
            break;
        case ApplicationState::STATE_SHUTDOWN:
            ui.shutdown();
            game.shutdown();
            shutdown();
            break;
        default:
            break;
        }
        
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


void Application::updateUserInputs(sf::Event _event)
{
    // "close requested" event: we close the window
    if (_event.type == sf::Event::Closed)
        window.close();

    if (_event.type == sf::Event::KeyPressed)
        ;


    /// MOUSE CONTROL ///
    if (mouse.clicked_left)
        mouse.clicked_left = false;

    if (mouse.clicked_right)
        mouse.clicked_right = false;

    if (mouse.pressed_left)
    {
        if (_event.type == sf::Event::MouseButtonReleased)
        {
            if (_event.mouseButton.button == sf::Mouse::Left)
            {
                mouse.clicked_left = true;
                mouse.pressed_left = false;
            }
        }
    }

    if (mouse.pressed_right)
    {
        if (_event.type == sf::Event::MouseButtonReleased)
        {
            if (_event.mouseButton.button == sf::Mouse::Right)
            {
                mouse.clicked_right = true;
                mouse.pressed_right = false;
            }   
        }
    }

    
    if (_event.type == sf::Event::MouseButtonPressed)
    {
        if (_event.mouseButton.button == sf::Mouse::Left)
            mouse.pressed_left = true;
        if (_event.mouseButton.button == sf::Mouse::Right)
            mouse.pressed_right = true;
    }

    if (_event.type == sf::Event::MouseMoved)
    {
        mouse.pos = sf::Vector2f(_event.mouseMove.x, _event.mouseMove.y);
    }
    /// ~MOUSE CONTROL ///
}
