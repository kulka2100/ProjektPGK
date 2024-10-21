#pragma once
#include "Player.h"
#include "Background.h"
#include "Menu.h"

class Game
{
private:
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
	
	Game();

	~Game();

	sf::RenderWindow& getWindow();


	void updatePlayer(float deltaTime);

	void renderPlayer();

	void renderBackground();

	void update();

	void render();
};

