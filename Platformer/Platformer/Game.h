#pragma once
#include "Player.h"
#include "Background.h"
#include "Menu.h"

class Game
{
private:
	int width; 
	int height; 
	sf::Event event;
	sf::RenderWindow window;
	sf::Clock clock;

	Player *player;
	Background* background;
	Menu* menu;
	bool isMenuActive;
	bool isPlayed;

	void initWindow();
	void initPlayer();
	void initBackground();

public:
	
	Game(int width, int height);

	~Game();

	sf::RenderWindow& getWindow();


	void updatePlayer(float deltaTime);

	void renderPlayer();

	void renderBackground();

	void update();

	void render();

	int getWidth() {
		return width;
	}

	int getHeight() {
		return height;
	}
};

