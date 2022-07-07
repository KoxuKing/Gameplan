#pragma once
#include "GameTable.h"
class ConnectFourTable : public GameTable
{
public:
	ConnectFourTable();
	virtual void update(class Player* _player, class Application* _application);
	virtual void shutdown();

	const static int lastRow = 6;
	const static int lastColumn = 7;

	int board[lastRow][lastColumn] =
	{
	{0, 0, 0, 0, 0, 0, 0},
	{0, 0, 0, 0, 0, 0, 0},
	{0, 0, 0, 0, 0, 0, 0},
	{0, 0, 0, 0, 0, 0, 0},
	{0, 0, 0, 0, 0, 0, 0},
	{0, 0, 0, 0, 0, 0, 0}
	};

	bool isStraight(int _row, int _column);
	sf::Vector2i latestToken;
	bool isAnimationOn;

	std::vector<struct Token*> tokenVector; // Uutta
	
protected:
	virtual void drawTable(class Application* _application);

private:
	sf::RectangleShape addTokenArea;
	

	const int getColumn(int _mousePosX);
	
	sf::Texture tokenTextures[2];
	sf::Sprite redTokenSprite;
	sf::Sprite yellowTokenSprite;

	void drawTokens(Application* _application);
	void dropTokenAnimation(Application* _application);
	void playAnimation(Application* _application);
	float animationPos;
};



