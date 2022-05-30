#include "application.h"

int application::run()
{
    while(true)
    {
        updateUserInputs();

        switch (State)
        {
        case ApplicationState::STATE_GAME:
            // if (game)
                // game.update();
            break;
        case ApplicationState::STATE_UI:
            // ui.update();
            break;
        default:
            break;
        }
    }
    return 0;
}

int application::shutdown()
{
    return 0;
}


void application::updateUserInputs()
{
    // update mouseposition
    // update keypressed
}
