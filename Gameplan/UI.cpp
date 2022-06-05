#include "UI.h"
#include "application.h"
#include "Button.h"

UI::UI(Application *_application)
{
    application = _application;

    // Create main menu
    mainmenu = new Window("Textures/UiTesti2.PNG", 1, 1, application->window_width, application->window_width);
    // inputs: x-pos, y-pos, width, height
	Button *button = new Button((application->window_width/2) - 50, 50, 100, 50);
    button->setText("Options", 0, 0);
    button->changeState = UI::STATE_OPTIONS;
    mainmenu->buttonList.push_back(button);

    button = new Button((application->window_width / 2) - 50, 200, 100, 50);
    mainmenu->buttonList.push_back(button);

    Button* button3 = new Button((application->window_width / 2) - 50, 350, 100, 50);
    mainmenu->buttonList.push_back(button3);

    //create options
    options = new Window("Textures/Sieppaa.PNG", 0, 0, application->window_width, application->window_width);
    // inputs: x-pos, y-pos, width, height
    Button* button1 = new Button((application->window_width / 2) - 100, 50, 200, 50);
    button1->changeState = UI::STATE_MAIN_MENU;
    options->buttonList.push_back(button1);
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
    default:
        break;
    }

    // draw active ui
    drawUi();
    checkButtons();
   
	return 0;
}

void UI::drawUi()
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

void UI::checkButtons()
{
   // loop trough buttons of active window
    for (UiInput* button : activeWindow->buttonList)
    {
        if (button->isSelected(application))
        {
            if (application->mouse.clicked_left)
            {
                button->click(application);
                application->mouse.clicked_left = false;
            }
        }
    }
}

int UI::shutdown()
{
    for (UiInput* input : mainmenu->buttonList)
        delete input;
    delete mainmenu;

    for (UiInput* input : options->buttonList)
        delete input;
    delete options;
	return 0;
}



