#pragma once
#include "UiInput.h"
#include "SFML/Graphics.hpp"
#include <string>
class UiTextInput : public UiInput
{
public:
	UiTextInput(int _x, int _y, int _maxChar);
	virtual void draw(class Application* _application);
	void setPlaceholder(std::string _placeholder);
	std::string inputText = "";


private:
	std::string placeholder = "";
	int maxChar;
	int charAmount = 0;
	float timePassedFromLastInput;
	bool isFirstChar = true;
	std::vector<char> inputTextVector;
	void updateInput(class Application* _application);

	void charVectorToString();


};

