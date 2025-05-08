#pragma once
#include "GameTable.h"
class ConnectFourTable : public GameTable
{
public:
	ConnectFourTable();
	virtual void update(class Player* _player, class Application* _application);
	//virtual void shutdown();
	virtual void unfocusTable();
	virtual void focusTable();


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
	sf::Vector2f tokenPos;
	bool isAnimationOn;

	std::vector<struct Token*> atokenVector; // Turha mutta ei toimi ilman?
	
protected:
	void drawTable(class Application* _application) override;

private:
	sf::RectangleShape addTokenArea;
	float animationStartTime;

	const int getColumn(int _mousePosX);
	sf::Text turnTime;
	sf::Texture tokenTextures[2];
	sf::Sprite redTokenSprite;
	sf::Sprite yellowTokenSprite;

	void drawTokens(Application* _application);
	void dropTokenAnimation(Application* _application);
	void playAnimation(Application* _application);
	float animationPos{};
};



