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
    if (!mainmenu->texturePath.empty()) {
        backgroundImage = getTexture(mainmenu->texturePath);
    }
}

sf::Texture& UI::getTexture(const std::string& path)
{
    // Check if texture already loaded
    auto it = textureCache.find(path);
    if (it == textureCache.end()) {
        // Texture not found, load it
        sf::Texture newTexture;
        if (!newTexture.loadFromFile(path)) {
            std::cerr << "Warning: Failed to load texture: " << path << std::endl;
        }
        auto result = textureCache.emplace(path, std::move(newTexture));
        return result.first->second;
    }
    
    // Return cached texture
    return it->second;
}

Button* UI::createStandardButton(int x, int y, int width, int height, const std::string& text, 
                                UiState state, const std::string& texturePath)
{
    Button* button = new Button(x, y, width, height);
    if (!text.empty()) {
        button->setText(text);
    }
    button->changeState = state;
    if (!texturePath.empty()) {
        button->setTexture(texturePath);
    }
    return button;
}

void UI::createMainMenu()
{
    std::string buttonTexturePath = "Textures/testTexture.png";
    
    // Create main menu window
    mainmenu = std::make_unique<Window>("Textures/UiTesti2.PNG", 1, 1, application->window_width, application->window_height);
    
    // Options button
    Button *button = createStandardButton(centerX(100), 200, 100, 50, "Options", UI::STATE_OPTIONS, buttonTexturePath);
    mainmenu->buttonList.push_back(button);
    
    // Game Selection button
    button = createStandardButton(centerX(150), 50, 150, 50, "Select game", UI::STATE_GAME_SELECTION, buttonTexturePath);
    mainmenu->buttonList.push_back(button);
    
    // Quit button
    button = createStandardButton(centerX(100), 350, 100, 50, "Quit", UI::STATE_QUIT, buttonTexturePath);
    mainmenu->buttonList.push_back(button);
    
    // Server IP text input
    UiTextInput *textInput = new UiTextInput(centerX(100), 550, 21);
    textInput->setPlaceholder("Server ip:");
    mainmenu->buttonList.push_back(textInput);
}

void UI::createOptionsMenu()
{
    std::string buttonTexturePath = "Textures/testTexture.png";
    
    // Create options window
    options = std::make_unique<Window>("Textures/UiTesti2.PNG", 0, 0, application->window_width, application->window_height);
    
    // Return button
    Button *button = createStandardButton(centerX(STANDARD_BUTTON_WIDTH), 50, STANDARD_BUTTON_WIDTH, STANDARD_BUTTON_HEIGHT, "Return", UI::STATE_MAIN_MENU, buttonTexturePath);
    button->setReturnButton(true);
    options->buttonList.push_back(button);
    
    // Volume slider
    Slider* slider = new Slider(centerX(200), 250, 200);
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
    Button *button = createStandardButton(centerX(STANDARD_BUTTON_WIDTH), 50, STANDARD_BUTTON_WIDTH, STANDARD_BUTTON_HEIGHT, 
                                         "Connect Four", UiState::STATE_GAME, buttonTexturePath);
    button->buttonAttribute = "ConnectFour";
    gameSelection->buttonList.push_back(button);
    
    // Checkers button
    button = createStandardButton(centerX(STANDARD_BUTTON_WIDTH), 150, STANDARD_BUTTON_WIDTH, STANDARD_BUTTON_HEIGHT, 
                                 "Checkers", UiState::STATE_GAME, buttonTexturePath);
    button->buttonAttribute = "Checkers";
    gameSelection->buttonList.push_back(button);
    
    // Main Menu button
    button = createStandardButton(centerX(STANDARD_BUTTON_WIDTH), 350, STANDARD_BUTTON_WIDTH, STANDARD_BUTTON_HEIGHT, 
                                 "Main menu", UiState::STATE_MAIN_MENU, buttonTexturePath);
    gameSelection->buttonList.push_back(button);
}

void UI::createEndGameWindow()
{
    std::string buttonTexturePath = "Textures/testTexture.png";
    
    // Create end game window
    endGameWindow = std::make_unique<Window>("", 100, 150, application->window_width - 200, application->window_height - 500);
    
    // Play Again button
    Button *button = createStandardButton((application->window_width/4)-50, 175, STANDARD_BUTTON_WIDTH, STANDARD_BUTTON_HEIGHT, 
                                         "Play again", UiState::STATE_GAME, buttonTexturePath);
    endGameWindow->buttonList.push_back(button);
    
    // Main Menu button
    button = createStandardButton((application->window_width/4)*2 + 50, 175, STANDARD_BUTTON_WIDTH, STANDARD_BUTTON_HEIGHT, 
                                 "Main menu", UiState::STATE_MAIN_MENU, buttonTexturePath);
    endGameWindow->buttonList.push_back(button);
}

void UI::createInGameUI()
{
    std::string buttonTexturePath = "Textures/menuButton.png";
    
    // Create in-game UI window
    inGame = std::make_unique<Window>("", 0, 0, application->window_width, application->window_height);
    
    // Menu button
    Button* button = createStandardButton(5, 5, 50, 50, "", UiState::STATE_GAME_MENU, buttonTexturePath);
    inGame->buttonList.push_back(button);
}

void UI::createInGameMenu()
{
    std::string buttonTexturePath = "Textures/testTexture.png";
    
    // Create in-game menu window
    inGameMenu = std::make_unique<Window>("", application->window_width / 2 - 150, application->window_height / 2 - 150, 300, 300);
    
    // Options button
    Button* button = createStandardButton((inGameMenu->width / 2 + inGameMenu->x) - 100, inGameMenu->y + 50, 
                                         STANDARD_BUTTON_WIDTH, STANDARD_BUTTON_HEIGHT, "Options", UiState::STATE_OPTIONS, buttonTexturePath);
    inGameMenu->buttonList.push_back(button);
    
    // Quit button
    button = createStandardButton((inGameMenu->width / 2 + inGameMenu->x) - 100, inGameMenu->y + 125, 
                                 STANDARD_BUTTON_WIDTH, STANDARD_BUTTON_HEIGHT, "Quit", UiState::STATE_MAIN_MENU, buttonTexturePath);
    inGameMenu->buttonList.push_back(button);
    
    // Back button
    button = createStandardButton((inGameMenu->width / 2 + inGameMenu->x) - 100, inGameMenu->y + 200, 
                                 STANDARD_BUTTON_WIDTH, STANDARD_BUTTON_HEIGHT, "Back", UiState::STATE_GAME, buttonTexturePath);
    inGameMenu->buttonList.push_back(button);
}

void UI::createLobbyWindow()
{
    std::string buttonTexturePath = "Textures/testTexture.png";
    
    // Create game lobby window
    lobby = std::make_unique<Window>("Textures/testTexture.png", 100, 150, application->window_width - 200, application->window_height - 200);
    
    // Add button
    Button *button = createStandardButton((application->window_width / 4) - 50, 175, STANDARD_BUTTON_WIDTH, STANDARD_BUTTON_HEIGHT, 
                                         "Join Game", UiState::STATE_MAIN_MENU, buttonTexturePath);
    lobby->buttonList.push_back(button);
}

void UI::loadBackgroundForState(Window* window)
{
    if (!window) {
        std::cerr << "Warning: Attempting to load background for null window" << std::endl;
        return;
    }
    
    if (window->texturePath.empty()) {
        return; // No background to load
    }
    
    if (activeWindow != window || backgroundImage.getSize().x == 0) {
        backgroundImage = getTexture(window->texturePath);
    }
}

int UI::centerX(int width) const
{
    if (!application) {
        // Handle null pointer case, perhaps return 0 or throw an exception
        return 0;
    }
    return (application->window_width / 2) - (width / 2);
}
int UI::centerY(int height) const
{
    if (!application) {
        // Handle null pointer case, perhaps return 0 or throw an exception
        return 0;
    }
    return (application->window_height / 2) - (height / 2);
}

int UI::update()
{
    Window* nextActiveWindow = nullptr;
    
    switch (State) {
    case UiState::STATE_MAIN_MENU:
        nextActiveWindow = mainmenu.get();
        break;
        
    case UiState::STATE_OPTIONS:
        nextActiveWindow = options.get();
        break;
        
    case UiState::STATE_GAME_SELECTION:
        nextActiveWindow = gameSelection.get();
        break;
        
    case UiState::STATE_GAME:
        if (!application->game.isGameOn) {
            application->game.isGameOn = true;
        }
        application->State = Application::ApplicationState::GAME;
        nextActiveWindow = inGame.get();
        break;
        
    case UiState::STATE_ENDGAME:
        nextActiveWindow = endGameWindow.get();
        break;
        
    case UiState::STATE_GAME_MENU:
        application->game.isGameOn = false;
        nextActiveWindow = inGameMenu.get();
        break;
        
    case UiState::STATE_QUIT:
        activeWindow = nullptr;
        application->State = Application::ApplicationState::SHUTDOWN;
        break;
        
    default:
        break;
    }
    
    if (nextActiveWindow) {
        loadBackgroundForState(nextActiveWindow);
        activeWindow = nextActiveWindow;
    }
    
    if (State != UiState::STATE_QUIT) {
        drawUi();
        checkButtons();
    }
    
    return 0;
}

void UI::drawUi()
{
    if (!activeWindow) {
        return;
    }
    
    if (!activeWindow->texturePath.empty()) {
        sf::Sprite sprite;
        sprite.setTexture(backgroundImage);
        
        if (sprite.getLocalBounds().width > 0 && sprite.getLocalBounds().height > 0) {
            sprite.setScale(
                activeWindow->width / sprite.getLocalBounds().width,
                activeWindow->height / sprite.getLocalBounds().height
            );
            sprite.setPosition(activeWindow->x, activeWindow->y);
            application->window.draw(sprite);
        }
    }
    
    for (UiInput* input : activeWindow->buttonList) {
        if (input) {
            input->draw(application);
        }
    }
}

void UI::checkButtons()
{
    if (!activeWindow) {
        return;
    }
    
    for (UiInput* button : activeWindow->buttonList) {
        if (!button) {
            continue;
        }
        
        if (application->mouse.clicked_left) {
            button->wasSelected = false;
        }

        if (application->mouse.pressed_left && button->wasSelected) {
            button->press(application);
        }

        if (button->isSelected(application)) {
            if (application->mouse.clicked_left) {
                button->click(application);
                application->mouse.clicked_left = false;
            }
            if (application->mouse.pressed_left) {
                button->press(application);
                button->wasSelected = true;
            }
        }
    }
}

int UI::shutdown()
{
    // Helper function to clean up button lists
    auto cleanupButtonList = [](std::unique_ptr<Window>& window) {
        if (window && !window->buttonList.empty()) {
            for (UiInput* input : window->buttonList) {
                delete input;
            }
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
    
    // Clear the texture cache
    textureCache.clear();
    
    std::cout << "UI shutdown completed successfully" << std::endl;
    
    return 0;
}



