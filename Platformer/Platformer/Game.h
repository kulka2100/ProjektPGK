#pragma once
#include "Player.h"
#include "Background.h"
#include "Menu.h"
#include "Maps.h"
#include "Obstacle.h"
#include "TextureManager.h"
#include "Enemy.h"
#include "GameState.h"
#include "CollectableItem.h"
#include "Moles.h"
#include "MapInitializer.h"
#include "Cats.h"
#include "Bats.h"
#include "Settings.h"
#include "Boss.h"
#include "Pause.h"



class Game
{
private:
	int width; 
	int height; 
	sf::Event event;
	sf::RenderWindow window;
	sf::Clock clock;
	std::vector<Enemy*> enemies;
	float deltaTime;
	

	Player *player;
	Background* background;
	Menu* menu;
	Maps* maps;
	Settings* settings;
	Pause* pause;
	MapInitializer* mapInitializer;
	TextureManager textureManager;
	std::vector<Obstacle> obstacles;
	std::vector<CollectableItem> collectableItems;
	std::vector<CollectableItem> carrotOnTree;
	bool isMenuActive;
	bool isPlayed;
	GameState gameState;
	int currentMap = 0;

	bool moveLeftObstacle = true;
	bool moveRightObstacle = false;

	void initWindow();
	void initPlayer();
	void initBackground(int mapIndex);
	void initObstacles(int mapIndex);
	void initCollectableItems(int mapIndex);
	void initEnemies();
	void updateEnemies(float deltaTime);
	void renderEnemies();
	void checkPlayerEnemyCollision();
	void checkBulletEnemyCollision();
	void checkBulletPlayerCollision();

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

	void updateCollectableItems(float deltaTime);
	
	void renderCollectableItems();
	
	void updateObstacles(float deltaTime);

	void renderObstacles();

	void updateBackground(float deltaTime, float characterSpeed);

	void renderBackground();

	void update();

	void render();

	void updateDeltaTime();

	void setOpenChestTexture();

};

