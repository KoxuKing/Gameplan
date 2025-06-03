#include "UI.h"
#include "../application.h"
#include "Button.h"
#include "UiSlider.h"
#include "UiTextInput.h"
#include <memory>
#include <iostream>

/**
 * Creates the main menu window
 */
void UI::createMainMenu()
{
    std::string buttonTexturePath = "Textures/testTexture.png";
    
    // Create main menu window
    mainmenu = std::make_unique<Window>("Textures/UiTesti2.PNG", 1, 1, application->window_width, application->window_height);
    
    // Options button
    std::unique_ptr<Button> button = createStandardButton(centerX(100), 200, 100, 50, "Options", buttonTexturePath);
    
    button->setCallback([this]() {
        application->ui.State = UI::STATE_OPTIONS;
        std::cout << "Select options menu" << std::endl;
        });
    
    mainmenu->buttonList.push_back(std::move(button));
    
    // Game Selection button
    button = createStandardButton(centerX(150), 50, 150, 50, "Select game", buttonTexturePath);
    
    button->setCallback([this]() {
        application->ui.State = UI::STATE_GAME_SELECTION;
        std::cout << "Select game selection menu" << std::endl;
        });

    mainmenu->buttonList.push_back(std::move(button));
    
    // Quit button
    button = createStandardButton(centerX(100), 350, 100, 50, "Quit", buttonTexturePath);

    button->setCallback([this]() {
        application->ui.State = UI::STATE_QUIT;
        std::cout << "Quit" << std::endl;
        });

    mainmenu->buttonList.push_back(std::move(button));
    
    // Server IP text input
    std::unique_ptr<UiTextInput> textInput = std::make_unique<class UiTextInput>(centerX(100), 550, 21);
    textInput->setPlaceholder("Server ip:");
    mainmenu->buttonList.push_back(std::move(textInput));
}

/**
 * Creates the options menu window
 */
void UI::createOptionsMenu()
{
    std::string buttonTexturePath = "Textures/testTexture.png";
    
    // Create options window
    options = std::make_unique<Window>("Textures/UiTesti2.PNG", 0, 0, application->window_width, application->window_height);
    
    // Return button
    std::unique_ptr<Button> button = createStandardButton(centerX(STANDARD_BUTTON_WIDTH), 50, STANDARD_BUTTON_WIDTH, STANDARD_BUTTON_HEIGHT, "Return", buttonTexturePath);

    button->setCallback([this]() {
        application->ui.State = UI::STATE_MAIN_MENU;
        std::cout << "Back to main menu" << std::endl;
        });

    options->buttonList.push_back(std::move(button));
    
    // Volume slider
    std::unique_ptr<Slider> slider = std::make_unique<Slider>(centerX(200), 250, 200);
    slider->setParameter(&application->volume, 100);
    slider->setText("Sound: ");
    options->buttonList.push_back(std::move(slider));
}

/**
 * Creates the game selection menu window
 */
void UI::createGameSelectionMenu()
{
    std::string buttonTexturePath = "Textures/testTexture.png";
    
    // Create game selection window
    gameSelection = std::make_unique<Window>("Textures/UiTesti2.PNG", 0, 0, application->window_width, application->window_height);
    
    // Connect Four button
    std::unique_ptr<Button> button = createStandardButton(centerX(STANDARD_BUTTON_WIDTH), 50, STANDARD_BUTTON_WIDTH, STANDARD_BUTTON_HEIGHT,
                                         "ConnectFour", buttonTexturePath);

    button->setCallback([this]() {
        application->game.selectGame("Connect Four");
		application->ui.State = UiState::STATE_GAME;
        std::cout << "Connect Four selected" << std::endl;
        });

    gameSelection->buttonList.push_back(std::move(button));
    
    // Checkers button
    button = createStandardButton(centerX(STANDARD_BUTTON_WIDTH), 150, STANDARD_BUTTON_WIDTH, STANDARD_BUTTON_HEIGHT, 
                                 "Checkers", buttonTexturePath);

    button->setCallback([this]() {
        application->game.selectGame("Checkers");
        application->ui.State = UiState::STATE_GAME;
        std::cout << "Checkers selected" << std::endl;
        });

    gameSelection->buttonList.push_back(std::move(button));
    
    // Main Menu button
    button = createStandardButton(centerX(STANDARD_BUTTON_WIDTH), 350, STANDARD_BUTTON_WIDTH, STANDARD_BUTTON_HEIGHT, 
                                 "Main menu", buttonTexturePath);

    button->setCallback([this]() {
        application->ui.State = UI::STATE_MAIN_MENU;
        std::cout << "Back to main menu" << std::endl;
        });

    gameSelection->buttonList.push_back(std::move(button));
}

/**
 * Creates the end game window
 */
void UI::createEndGameWindow()
{
    std::string buttonTexturePath = "Textures/testTexture.png";
    
    // Create end game window
    endGameWindow = std::make_unique<Window>("", 100, 150, application->window_width - 200, application->window_height - 500);
    
    // Play Again button
    std::unique_ptr<Button> button = createStandardButton(centerX(STANDARD_BUTTON_WIDTH), 175, STANDARD_BUTTON_WIDTH, STANDARD_BUTTON_HEIGHT,
                                         "Play again", buttonTexturePath);

    button->setCallback([this]() {
        application->ui.State = UI::STATE_GAME;
        std::cout << "Back to game" << std::endl;
        });

    endGameWindow->buttonList.push_back(std::move(button));
    
    // Main Menu button
    button = createStandardButton(centerX(STANDARD_BUTTON_WIDTH), 175, STANDARD_BUTTON_WIDTH, STANDARD_BUTTON_HEIGHT,
                                 "Main menu", buttonTexturePath);

    button->setCallback([this]() {
        application->ui.State = UI::STATE_MAIN_MENU;
        std::cout << "Back to main menu" << std::endl;
        });

    endGameWindow->buttonList.push_back(std::move(button));
}

/**
 * Creates the in-game UI
 */
void UI::createInGameUI()
{
    std::string buttonTexturePath = "Textures/menuButton.png";
    
    // Create in-game UI window
    inGame = std::make_unique<Window>("", 0, 0, application->window_width, application->window_height);
    
    // Menu button
    std::unique_ptr<Button> button = createStandardButton(5, 5, 50, 50, "", buttonTexturePath);

    button->setCallback([this]() {
        application->ui.State = UI::STATE_GAME_MENU;
        std::cout << "Select game menu" << std::endl;
        });

    inGame->buttonList.push_back(std::move(button));
}

/**
 * Creates the in-game menu window
 */
void UI::createInGameMenu()
{
    std::string buttonTexturePath = "Textures/testTexture.png";
    
    // Create in-game menu window
    inGameMenu = std::make_unique<Window>("", application->window_width / 2 - 150, application->window_height / 2 - 150, 300, 300);
    
    // Options button
    std::unique_ptr<Button> button = createStandardButton(centerX(STANDARD_BUTTON_WIDTH), inGameMenu->y + 50,
                                         STANDARD_BUTTON_WIDTH, STANDARD_BUTTON_HEIGHT, "Options", buttonTexturePath);
    
    button->setCallback([this]() {
        application->ui.State = UI::STATE_OPTIONS;
        std::cout << "Select options" << std::endl;
        });
    
    inGameMenu->buttonList.push_back(std::move(button));
    
    // Quit button
    button = createStandardButton(centerX(STANDARD_BUTTON_WIDTH), inGameMenu->y + 125,
                                 STANDARD_BUTTON_WIDTH, STANDARD_BUTTON_HEIGHT, "Quit", buttonTexturePath);
    
    button->setCallback([this]() {
        application->ui.State = UI::STATE_MAIN_MENU;
        std::cout << "Select main menu" << std::endl;
        });
    
    inGameMenu->buttonList.push_back(std::move(button));
    
    // Back button
    button = createStandardButton(centerX(STANDARD_BUTTON_WIDTH), inGameMenu->y + 200,
                                 STANDARD_BUTTON_WIDTH, STANDARD_BUTTON_HEIGHT, "Back", buttonTexturePath);
    
    button->setCallback([this]() {
        application->ui.State = UI::STATE_GAME;
        std::cout << "Back to game" << std::endl;
        });
    
    inGameMenu->buttonList.push_back(std::move(button));
}

/**
 * Creates the lobby window
 */
void UI::createLobbyWindow()
{
    std::string buttonTexturePath = "Textures/testTexture.png";
    
    // Create game lobby window
    lobby = std::make_unique<Window>("Textures/testTexture.png", 100, 150, application->window_width - 200, application->window_height - 200);
    
    // Add button
    std::unique_ptr<Button> button = createStandardButton(centerX(STANDARD_BUTTON_WIDTH), 175, STANDARD_BUTTON_WIDTH, STANDARD_BUTTON_HEIGHT,
                                         "Join Game", buttonTexturePath);
    lobby->buttonList.push_back(std::move(button));
}