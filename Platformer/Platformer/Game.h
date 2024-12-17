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
#include <fstream>



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
	int difficultyLvel = 0;

	bool moveLeftObstacle = true;
	bool moveRightObstacle = false;
	bool isGameLoaded = false;

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

	void saveToBinaryFile(const std::string& filename) {
		std::ofstream file(filename);  // Otwieramy plik binarnie
		if (!file.is_open()) {
			std::cerr << "Nie mo¿na otworzyæ pliku do zapisu!" << std::endl;
			return;
		}

		std::cout << "File opened successfully." << std::endl;

		// Przyk³ad zapisu wartoœci
		try {
			float playerPosX = player->getPlayerPosition().x;
			float playerPosY = player->getPlayerPosition().y;
			file.write(reinterpret_cast<char*>(&playerPosX), sizeof(playerPosX));
			file.write(reinterpret_cast<char*>(&playerPosY), sizeof(playerPosY));
		}
		catch (const std::exception& e) {
			std::cerr << "Exception during file write: " << e.what() << std::endl;
			file.close();
			return;
		}

		file.close();
		std::cout << "File saved and closed successfully." << std::endl;
	}

	void loadFromFile(const std::string& filename) {
		std::ifstream file(filename, std::ios::binary);  // Otwieramy plik binarnie
		if (!file.is_open()) {
			std::cerr << "Nie mo¿na otworzyæ pliku do odczytu!" << std::endl;
			return;
		}
			// Zapis pozycji gracza (x i y)
		float playerPosX = player->getPlayerPosition().x;
		float playerPosY = player->getPlayerPosition().y;


		// Odczytujemy podstawowe dane obiektu Game
		file.read(reinterpret_cast<char*>(&width), sizeof(width));
		file.read(reinterpret_cast<char*>(&height), sizeof(height));
		file.read(reinterpret_cast<char*>(&gameState), sizeof(gameState));

		// Odczytujemy dane gracza (Player)
		if (player != nullptr) {
			file.read(reinterpret_cast<char*>(player->getCurrentHealth()), sizeof(player->getCurrentHealth()));
			file.read(reinterpret_cast<char*>(&playerPosX), sizeof(playerPosX));
			file.read(reinterpret_cast<char*>(&playerPosY), sizeof(playerPosY));
		}

		// Dodaj inne elementy gry (t³o, przeszkody, przedmioty, itp.)
		std::cout << "Stan gry odczytany z pliku binarnie: " << filename << std::endl;
		file.close();

		try {
			// Wczytaj pozycjê gracza
			float playerPosX, playerPosY;
			file.read(reinterpret_cast<char*>(&playerPosX), sizeof(playerPosX));
			file.read(reinterpret_cast<char*>(&playerPosY), sizeof(playerPosY));

			// Aktualizuj gracza na podstawie wczytanych danych
			player->getPlayerSprite().setPosition(playerPosX, playerPosY);

			std::cout << "Game loaded successfully!" << std::endl;
		}
		catch (const std::exception& e) {
			std::cerr << "Exception during file reading: " << e.what() << std::endl;
		}

		file.close();

		isGameLoaded = true;
	}

};

