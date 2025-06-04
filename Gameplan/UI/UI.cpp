#include "../application.h"
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
    activeWindow = mainmenu;
    
    // Load initial background for main menu
    if (!mainmenu->texturePath.empty()) {
        backgroundImage = getTexture(mainmenu->texturePath);
    }
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
    
    if (activeWindow.get() != window || backgroundImage.getSize().x == 0) {
        backgroundImage = getTexture(window->texturePath);
    }
}


int UI::update()
{
    std::shared_ptr<class Window> nextActiveWindow = nullptr;
    
    switch (State) {
    case UiState::STATE_MAIN_MENU:
        nextActiveWindow = mainmenu;
        break;
        
    case UiState::STATE_OPTIONS:
        nextActiveWindow = options;
        break;
        
    case UiState::STATE_GAME_SELECTION:
        nextActiveWindow = gameSelection;
        break;
        
    case UiState::STATE_GAME:
        if (!application->game.isGameOn) {
            application->game.isGameOn = true;
        }
        application->State = Application::ApplicationState::GAME;
        nextActiveWindow = inGame;
        break;
        
    case UiState::STATE_ENDGAME:
        nextActiveWindow = endGameWindow;
        break;
        
    case UiState::STATE_GAME_MENU:
        application->game.isGameOn = false;
        nextActiveWindow = inGameMenu;
        break;
        
    case UiState::STATE_QUIT:
        activeWindow = nullptr;
        application->State = Application::ApplicationState::SHUTDOWN;
        break;
        
    default:
        break;
    }
    
    if (nextActiveWindow) {
        loadBackgroundForState(nextActiveWindow.get());
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
    
    for (auto &input : activeWindow->buttonList) {
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
    
    for (auto &button : activeWindow->buttonList) {
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
    // Release texture cache references
    textureCache.clear();
    backgroundImage = sf::Texture();
    
    // Clean all windows
    mainmenu.reset();
    options.reset();
    gameSelection.reset();
    endGameWindow.reset();
    inGame.reset();
    inGameMenu.reset();
    lobby.reset();
    
    return 0;
}



