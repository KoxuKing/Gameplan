#pragma once
#include <iostream>
#include "application.h"
#include <SFML/Audio.hpp>

class UiInput
{
public:
	UiInput() {};

	virtual bool isSelected(class Application* _application);
	virtual bool isClicked() const;

	virtual void press(class Application* _application);
	virtual void click(Application* _application) const;
	virtual void select();

	virtual void draw(class Application* _application);

	virtual void setText(std::string _text, int _x = 0, int _y = 0);
	virtual void playSound(float& _volume);
	bool wasSelected = false;
	

protected:
	sf::Vector2f size;
	int x;
	int y;
	sf::Color color;
	bool selected;

	// Ehkä structi tekstille??
	sf::Text text;
	sf::Color textColor = sf::Color::Black;
	sf::Font textFont;
	unsigned int textCharacterSize;
	sf::Sound sound;
	sf::SoundBuffer soundbuffer;

	// for testing
	// std::string path_to_buttontexture;
	// std::string path_to_buttonselectedtexture;
};

