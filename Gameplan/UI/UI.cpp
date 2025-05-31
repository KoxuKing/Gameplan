#include "UI.h"
#include "../application.h"
#include "Button.h"
#include "UiSlider.h"
#include "UiTextInput.h"
#include <memory>
#include <iostream>

UI::UI(Application *_application)
{
    application = _application;
    
    // Create all UI windows
    createMainMenu();
    createOptionsMenu();
    createGameSelectionMenu();
    createEndGameWindow();
    createInGameUI();
    createInGameMenu();
    createLobbyWindow();
    
    // Set initial active window
    activeWindow = mainmenu.get();
    
    // Load initial background for main menu
    if (!mainmenu->texturePath.empty() && !backgroundImage.loadFromFile(mainmenu->texturePath)) {
        std::cerr << "Warning: Failed to load main menu background: " << mainmenu->texturePath << std::endl;
    }
}

void UI::createMainMenu()
{
    std::string buttonTexturePath = "Textures/testTexture.png";
    
    // Create main menu window
    mainmenu = std::make_unique<Window>("Textures/UiTesti2.PNG", 1, 1, application->window_width, application->window_height);
    
    // Options button
    Button *button = new Button((application->window_width/2) - 50, 200, 100, 50);
    button->setText("Options");
    button->changeState = UI::STATE_OPTIONS;
    button->setTexture(buttonTexturePath);
    mainmenu->buttonList.push_back(button);
    
    // Game Selection button
    button = new Button((application->window_width / 2) - 75, 50, 150, 50);
    button->changeState = UI::STATE_GAME_SELECTION;
    button->setText("Select game");
    button->setTexture(buttonTexturePath);
    mainmenu->buttonList.push_back(button);
    
    // Quit button
    button = new Button((application->window_width / 2) - 50, 350, 100, 50);
    button->changeState = UI::STATE_QUIT;
    button->setText("Quit");
    button->setTexture(buttonTexturePath);
    mainmenu->buttonList.push_back(button);
    
    // Server IP text input
    UiTextInput *textInput = new UiTextInput((application->window_width / 2) - 50, 550, 21);
    textInput->setPlaceholder("Server ip:");
    mainmenu->buttonList.push_back(textInput);
}

void UI::createOptionsMenu()
{
    std::string buttonTexturePath = "Textures/testTexture.png";
    
    // Create options window
    options = std::make_unique<Window>("Textures/UiTesti2.PNG", 0, 0, application->window_width, application->window_height);
    
    // Return button
    Button *button = new Button((application->window_width / 2) - 100, 50, 200, 50);
    button->setReturnButton(true);
    button->setText("Return");
    button->setTexture(buttonTexturePath);
    options->buttonList.push_back(button);
    
    // Volume slider
    Slider* slider = new Slider((application->window_width / 2)-100, 250, 200);
    slider->setParameter(&application->volume, 100);
    slider->setText("Sound: ");
    options->buttonList.push_back(slider);
}

void UI::createGameSelectionMenu()
{
    std::string buttonTexturePath = "Textures/testTexture.png";
    
    // Create game selection window
    gameSelection = std::make_unique<Window>("Textures/UiTesti2.PNG", 0, 0, application->window_width, application->window_height);
    
    // Connect Four button
    Button *button = new Button((application->window_width / 2) - 100, 50, 200, 50);
    button->changeState = UiState::STATE_GAME;
    button->buttonAttribute = "ConnectFour";
    button->setTexture(buttonTexturePath);
    button->setText("Connect Four");
    gameSelection->buttonList.push_back(button);
    
    // Checkers button
    button = new Button((application->window_width / 2) - 100, 150, 200, 50);
    button->changeState = UiState::STATE_GAME;
    button->buttonAttribute = "Checkers";
    button->setTexture(buttonTexturePath);
    button->setText("Checkers");
    gameSelection->buttonList.push_back(button);
    
    // Main Menu button
    button = new Button((application->window_width / 2) - 100, 350, 200, 50);
    button->changeState = UiState::STATE_MAIN_MENU;
    button->setTexture(buttonTexturePath);
    button->setText("Main menu");
    gameSelection->buttonList.push_back(button);
}

void UI::createEndGameWindow()
{
    std::string buttonTexturePath = "Textures/testTexture.png";
    
    // Create end game window
    endGameWindow = std::make_unique<Window>("", 100, 150, application->window_width - 200, application->window_height - 500);
    
    // Play Again button
    Button *button = new Button((application->window_width/4)-50, 175, 200, 50);
    button->changeState = UiState::STATE_GAME;
    button->setText("Play again");
    button->setTexture(buttonTexturePath);
    endGameWindow->buttonList.push_back(button);
    
    // Main Menu button
    button = new Button((application->window_width / 4)*2 + 50, 175, 200, 50);
    button->changeState = UiState::STATE_MAIN_MENU;
    button->setText("Main menu");
    button->setTexture(buttonTexturePath);
    endGameWindow->buttonList.push_back(button);
}

void UI::createInGameUI()
{
    std::string buttonTexturePath = "Textures/menuButton.png";
    
    // Create in-game UI window
    inGame = std::make_unique<Window>("", 0, 0, application->window_width, application->window_height);
    
    // Menu button
    Button* button = new Button(5, 5, 50, 50);
    button->setTexture(buttonTexturePath);
    button->changeState = UiState::STATE_GAME_MENU;
    inGame->buttonList.push_back(button);
}

void UI::createInGameMenu()
{
    std::string buttonTexturePath = "Textures/testTexture.png";
    
    // Create in-game menu window
    inGameMenu = std::make_unique<Window>("", application->window_width / 2 - 150, application->window_height / 2 - 150, 300, 300);
    
    // Options button
    Button* button = new Button((inGameMenu->width / 2 + inGameMenu->x) - 100, inGameMenu->y + 50, 200, 50);
    button->setTexture(buttonTexturePath);
    button->setText("Options");
    button->changeState = UiState::STATE_OPTIONS;
    inGameMenu->buttonList.push_back(button);
    
    // Quit button
    button = new Button((inGameMenu->width / 2 + inGameMenu->x) - 100, inGameMenu->y + 125, 200, 50);
    button->setTexture(buttonTexturePath);
    button->setText("Quit");
    button->changeState = UiState::STATE_MAIN_MENU;
    inGameMenu->buttonList.push_back(button);
    
    // Back button
    button = new Button((inGameMenu->width / 2 + inGameMenu->x) - 100, inGameMenu->y + 200, 200, 50);
    button->setTexture(buttonTexturePath);
    button->setText("Back");
    button->changeState = UiState::STATE_GAME;
    inGameMenu->buttonList.push_back(button);
}

void UI::createLobbyWindow()
{
    std::string buttonTexturePath = "Textures/testTexture.png";
    
    // Create game lobby window
    lobby = std::make_unique<Window>("Textures/testTexture.png", 100, 150, application->window_width - 200, application->window_height - 200);
    
    // Add button
    Button *button = new Button((application->window_width / 4) - 50, 175, 200, 50);
    button->setTexture(buttonTexturePath);
    lobby->buttonList.push_back(button);
}

int UI::update()
{
    switch (State)
    {
    case UiState::STATE_MAIN_MENU:
    {
        if (backgroundImage.getSize().x == 0 && backgroundImage.getSize().y == 0 || activeWindow != mainmenu.get())
            if (!backgroundImage.loadFromFile(mainmenu->texturePath))
                std::cerr << "Warning: Failed to load main menu background: " << mainmenu->texturePath << std::endl;
        activeWindow = mainmenu.get();
        break;
    }
    case UiState::STATE_OPTIONS:
    {
        if (activeWindow != options.get())
            if (!backgroundImage.loadFromFile(options->texturePath))
                std::cerr << "Warning: Failed to load options background: " << options->texturePath << std::endl;
        activeWindow = options.get();
        break;
    }
    case UiState::STATE_GAME_SELECTION:
    {
        if (activeWindow != gameSelection.get())
            if (!backgroundImage.loadFromFile(gameSelection->texturePath))
                std::cerr << "Warning: Failed to load game selection background: " << gameSelection->texturePath << std::endl;
        activeWindow = gameSelection.get();
        break;
    }
    case UiState::STATE_GAME:
    {
        if (!application->game.isGameOn)
            application->game.isGameOn = true;

        application->State = Application::ApplicationState::GAME;

        if (activeWindow != inGame.get())
            if (!backgroundImage.loadFromFile(inGame->texturePath))
                std::cerr << "Warning: Failed to load in-game background: " << inGame->texturePath << std::endl;
        activeWindow = inGame.get();
        break;
    }
    case UiState::STATE_ENDGAME:
    {
        if (activeWindow != endGameWindow.get())
            if (!backgroundImage.loadFromFile(endGameWindow->texturePath))
                std::cerr << "Warning: Failed to load endgame background: " << endGameWindow->texturePath << std::endl;
        activeWindow = endGameWindow.get();
        break;
    }
    case UiState::STATE_GAME_MENU:
    {
        application->game.isGameOn = false;

        if (activeWindow != inGameMenu.get())
            if (!backgroundImage.loadFromFile(inGameMenu->texturePath))
                std::cerr << "Warning: Failed to load in-game menu background: " << inGameMenu->texturePath << std::endl;
        activeWindow = inGameMenu.get();
        break;
    }
    case UiState::STATE_QUIT:
    {
        activeWindow = nullptr; 
        application->State = Application::ApplicationState::SHUTDOWN;
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
        if (!activeWindow->texturePath.empty())
        {
            sf::Sprite sprite;
            sprite.setTexture(backgroundImage);
            sprite.setScale(activeWindow->width/sprite.getLocalBounds().width, activeWindow->height / sprite.getLocalBounds().height);
            sprite.setPosition(activeWindow->x, activeWindow->y);
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
    // Helper function to clean up button lists
    auto cleanupButtonList = [](std::unique_ptr<Window>& window) {
        if (window && !window->buttonList.empty()) {
            for (UiInput* input : window->buttonList)
                delete input;
            window->buttonList.clear();
        }
    };
    
    // Clean up all window button lists
    cleanupButtonList(mainmenu);
    cleanupButtonList(options);
    cleanupButtonList(gameSelection);
    cleanupButtonList(endGameWindow);
    cleanupButtonList(inGame);
    cleanupButtonList(inGameMenu);
    cleanupButtonList(lobby);
    
    return 0;
}



