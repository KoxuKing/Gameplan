#pragma once
#include <iostream>
#include "../application.h"
#include <SFML/Audio.hpp>

class UiInput
{
public:
	UiInput();

	virtual bool isSelected(class Application* _application);
	virtual bool isClicked() const;

	virtual void press(class Application* _application);
	virtual void click(Application* _application) const;
	virtual void select();

	virtual void draw(class Application* _application);

	virtual void setText(std::string _text);
	virtual void playSound(float& _volume);
	bool wasSelected = false;
	

protected:
	sf::Vector2f size;
	int x;
	int y;
	sf::Color color;
	sf::Color originalColor;
	bool selected;
	sf::RectangleShape rect;
	sf::Texture texture;
	sf::FloatRect boundingBox;

	// Ehkä structi tekstille??
	sf::Text text;
	sf::Color textColor = sf::Color::Black;
	sf::Font textFont;
	sf::Sound sound;
	sf::SoundBuffer soundbuffer;

	// for testing
	// std::string path_to_buttontexture;
	// std::string path_to_buttonselectedtexture;
};

