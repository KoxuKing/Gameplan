#include "application.h"

int Application::run()
{
    // Init window
    window.create(sf::VideoMode(window_width, window_height), "GamePlatform");
    window.setVerticalSyncEnabled(true);
    window.setFramerateLimit(fps);

    while(window.isOpen())
    {
        // check all the window's events that were triggered since the last iteration of the loop
        sf::Event event;
        while (window.pollEvent(event))
        {
            updateUserInputs(event);

            switch (State)
            {
            case ApplicationState::STATE_GAME:
                // if (game)
                    // game.update();
                break;
            case ApplicationState::STATE_UI:
                ui.update();
                break;
            default:
                break;
            }
        }
    }
    return 0;
}

int Application::shutdown()
{
    return 0;
}


void Application::updateUserInputs(sf::Event _event)
{
    // "close requested" event: we close the window
    if (_event.type == sf::Event::Closed)
        window.close();

    if (_event.type == sf::Event::KeyPressed)
        ;

    if (_event.type == sf::Event::MouseButtonPressed)
    {
        if (_event.mouseButton.button == sf::Mouse::Left)
            mouse.clicked_left = true;
        if (_event.mouseButton.button == sf::Mouse::Right)
            mouse.clicked_right = true;
    }
    else
    {
        mouse.clicked_left = false;
        mouse.clicked_right = false;
    }

    if (_event.type == sf::Event::MouseMoved)
    {
        mouse.x = _event.mouseMove.x;
        mouse.y = _event.mouseMove.y;
    }
}
