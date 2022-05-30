#pragma once
class UI
{
public:
	UI();
	int update();
	int shutdown();

	int State;
	enum UiState
	{
		STATE_MAIN_MENU = 0,
		STATE_OPTIONS = 1
	};
private:

	// UiWindow mainmenu;
	// UiWindow options;
	// UiWindow game_selection;
	// UiWindow pause_menu;
	struct Window
	{
		Window(int width, int height);
		// addButton(x, y, &button)
		// addCheckBox
		// addSlider
		// addTextBox
		// Texture backgroundImage;

		//std::vector<UiInputs*> buttonList;
	};
};

