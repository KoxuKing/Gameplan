#pragma once
#include "UiInput.h"
class Button : public UiInput
{
public:
	Button(int _x, int _y, float _width, float _height);

	virtual void click(Application* _application) const;
	
	mutable int changeState = -1;
	std::string buttonAttribute = "";

	void setReturnButton(bool _boolean);
	//typedef void (Game::* clientCallback)(sf::IpAddress, int);
	//clientCallback callBack;

	//template <typename T>
	//void addCallBack(void (T::* callBack)(sf::IpAddress, int));

private:
	bool isReturnButton = false;

};

