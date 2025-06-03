#pragma once
#include "UiInput.h"
#include "SFML/Graphics.hpp"
#include <string>
class UiTextInput : public UiInput
{
public:
	UiTextInput(float _x, float _y, unsigned int _maxChar);
	void draw(class Application* _application) override;
	void setPlaceholder(std::string _placeholder);
	std::string inputText = "";


private:
	std::string placeholder = "";
	unsigned int maxChar;
	int charAmount = 0;
	float timePassedFromLastInput;
	bool isFirstChar = true;
	std::vector<char> inputTextVector;
	void updateInput(class Application* _application);

	void charVectorToString();


};

