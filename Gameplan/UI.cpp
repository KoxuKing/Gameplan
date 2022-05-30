#include "UI.h"

UI::UI()
{
	// Luodaan kaikki käyttöliittymät
	//mainenu = Uiwindow(100, 100);

	//Button button1 = new Button();
	//mainmenu.addButton(10, 10, button1);

	//mainemnu.addButton();

	// options = Uiwindow(100, 100);

}

int UI::update()
{
	// logiikka koska mikäkin ui käytössä
    switch (State)
    {
    case UiState::STATE_MAIN_MENU:
        // active_window = mainmenu
        break;
    case UiState::STATE_OPTIONS:
        // active_window = options
        break;
    default:
        break;
    }

    // show active window
    //showWindow(active_window);

    // loop trough buttons of active window
    // for (Button button : active_window.buttonlist)
    // {
            // if(button.isSelected)
                // button.select();
            // if(button.isClicked)
                // button.click();
    
    
    // }
    

	return 0;
}

int UI::shutdown()
{
	return 0;
}

