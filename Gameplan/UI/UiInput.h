#pragma once
#include <iostream>
#include <functional>  // Add this for std::function
#include "../application.h"
#include <SFML/Audio.hpp>

class UiInput
{
public:
	UiInput();

	virtual bool isSelected(class Application* _application);
	virtual bool isClicked(Application* _application);

	virtual void press(class Application* _application);
	virtual void click(Application* _application) const;
	virtual void select();

	virtual void draw(class Application* _application);

	virtual void setText(std::string _text);
	virtual void playSound(float& _volume);

	void setTexture(std::string texturePath);
	bool wasSelected = false;

	// Generic callback that can work with any method from any class
	using InputCallback = std::function<void()>;
	void setCallback(InputCallback callback);

	std::string id;
	

protected:
	sf::Vector2f size;
	float x;
	float y;
	sf::Color color;
	sf::Color originalColor;
	bool selected;
	bool clicked;
	sf::RectangleShape rect;
	sf::Sprite sprite;
	sf::Texture texture;
	sf::FloatRect boundingBox;

	// Callback member - mutable to allow use in const methods
	mutable InputCallback m_callback = nullptr;

	// Ehkä structi tekstille??
	sf::Text text;
	sf::Color textColor = sf::Color::Black;
	sf::Font textFont;
	sf::Sound sound;
	sf::SoundBuffer soundbuffer;

	// for testing
	 std::string texturePath;
	// std::string path_to_buttonselectedtexture;
};

