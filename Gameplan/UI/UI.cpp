#include "UI.h"
#include "../application.h"
#include "Button.h"
#include "UiSlider.h"

UI::UI(Application *_application)
{
    application = _application;
    activeWindow = mainmenu;
    // Create main menu
    mainmenu = new Window("Textures/UiTesti2.PNG", 1, 1, application->window_width, application->window_width);
    // inputs: x-pos, y-pos, width, height
	Button *button = new Button((application->window_width/2) - 50, 200, 100, 50);
    button->setText("Options");
    button->changeState = UI::STATE_OPTIONS;
    mainmenu->buttonList.push_back(button);

    button = new Button((application->window_width / 2) - 75, 50, 150, 50);
    mainmenu->buttonList.push_back(button);
    button->changeState = UI::STATE_GAME_SELECTION;
    button->setText("Select game");

    Button* button3 = new Button((application->window_width / 2) - 50, 350, 100, 50);
    mainmenu->buttonList.push_back(button3);
    button3->changeState = UI::STATE_QUIT;
    button3->setText("Quit");

    //create options
    options = new Window("Textures/UiTesti2.PNG", 0, 0, application->window_width, application->window_width);
    // inputs: x-pos, y-pos, width, height
    Button* button1 = new Button((application->window_width / 2) - 100, 50, 200, 50);
    button1->changeState = UI::STATE_MAIN_MENU;
    options->buttonList.push_back(button1);
    button1->setText("Main menu");

    Slider* slider1 = new Slider((application->window_width / 2)-100, 250, 200);
    slider1->setParameter(&_application->volume, 100);
    slider1->setText("Sound: ");
    options->buttonList.push_back(slider1);

    //// create game selection window
    gameSelection = new Window("Textures/UiTesti2.PNG", 0, 0, application->window_width, application->window_width);
    Button* button5 = new Button((application->window_width / 2) - 100, 50, 200, 50);
    button5->changeState = UiState::STATE_GAME;
    gameSelection->buttonList.push_back(button5);
    button5->setText("Connect Four");
    Button* button4 = new Button((application->window_width / 2) - 100, 350, 200, 50);
    button4->changeState = UiState::STATE_MAIN_MENU;
    gameSelection->buttonList.push_back(button4);
    button4->setText("Main menu");
}

int UI::update()
{
    switch (State)
    {
    case UiState::STATE_MAIN_MENU:
    {
        activeWindow = mainmenu;
        break;
    }
    case UiState::STATE_OPTIONS:
    {
        activeWindow = options;
        break;
    }
    case UiState::STATE_GAME_SELECTION:
    {
        activeWindow = gameSelection;
        break;
    }
    case UiState::STATE_GAME:
    {
        application->State = Application::ApplicationState::STATE_GAME;
        activeWindow = nullptr;
        break;
    }
    case UiState::STATE_QUIT:
    {
        activeWindow = nullptr;
        application->State = Application::ApplicationState::STATE_SHUTDOWN;
        break;
    }
    default:
        break;
    }

    if (State != UiState::STATE_QUIT)
    {
        // draw active ui
        drawUi();
        checkButtons();
    }
	return 0;
}

void UI::drawUi()
{
    if (activeWindow != nullptr)
    {
        sf::Texture backgroundImage;
        if (backgroundImage.loadFromFile(activeWindow->texturePath, sf::IntRect(activeWindow->x,
            activeWindow->y,
            activeWindow->width,
            activeWindow->height)))
        {
            sf::Sprite sprite;
            sprite.setTexture(backgroundImage);
            application->window.draw(sprite);
        }

        for (UiInput* input : activeWindow->buttonList)
            input->draw(application);
    }
}

void UI::checkButtons()
{
   // loop trough buttons of active window
    if (activeWindow != nullptr)
    {
        for (UiInput* button : activeWindow->buttonList)
        {
            if (application->mouse.clicked_left)
                button->wasSelected = false;

            if (application->mouse.pressed_left && button->wasSelected)
                button->press(application);

            if (button->isSelected(application))
            {
                if (application->mouse.clicked_left)
                {
                    button->click(application);
                    application->mouse.clicked_left = false;
                }
                if (application->mouse.pressed_left)
                {
                    button->press(application);
                    button->wasSelected = true;
                }
            }
        }
    }
}

int UI::shutdown()
{
    if (mainmenu->buttonList.size() > 0)
    {
        for (UiInput* input : mainmenu->buttonList)
            delete input;
        delete mainmenu;
    }

    if (options->buttonList.size() > 0)
    {
        for (UiInput* input : options->buttonList)
            delete input;
        delete options;
    }

    if (gameSelection->buttonList.size() > 0)
    {
        for (UiInput* input : gameSelection->buttonList)
            delete input;
        delete gameSelection;
    }
    
	return 0;
}



