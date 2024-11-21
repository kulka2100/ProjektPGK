#pragma once
#include "Player.h"
#include "Background.h"
#include "Menu.h"
#include "Obstacle.h"
#include "TextureManager.h"
#include "Enemy.h"

class Game
{
private:
	int width; 
	int height; 
	sf::Event event;
	sf::RenderWindow window;
	sf::Clock clock;
	std::vector<Enemy> enemies;

	Player *player;
	Background* background;
	Menu* menu;
	TextureManager textureManager;
	std::vector<Obstacle> obstacles;
	bool isMenuActive;
	bool isPlayed;

	void initWindow();
	void initPlayer();
	void initBackground();
	void initObstacles();
	void initEnemies();
	void updateEnemies(float deltaTime);
	void renderEnemies();

public:
	
	Game(int width, int height);

	~Game();

	sf::RenderWindow& getWindow();

	int getWidth() {
		return width;
	}

	int getHeight() {
		return height;
	}


	void updatePlayer(float deltaTime);

	void renderPlayer();

	void updateObstacles();

	void renderObstacles();

	void updateBackground(float deltaTime, float characterSpeed);

	void renderBackground();

	void update();

	void render();

};

