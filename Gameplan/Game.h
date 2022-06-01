#pragma once
class Game
{
public:
	Game(class Application* _application);
	void update();
	void shutdown();
private:
	class Application* application;
};

