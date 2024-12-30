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
#include "Equipment.h"
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
	sf::Font font;
	

	Player *player;
	Background* background;
	Menu* menu;
	Maps* maps;
	Settings* settings;
	Pause* pause;
	Equipment* eq;
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
	int selectedEq = 0;

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
	void checkEqPanel();

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
		std::ofstream file(filename, std::ios::binary);  // Otwieramy plik binarnie
		if (!file.is_open()) {
			std::cerr << "Nie mo¿na otworzyæ pliku do zapisu!" << std::endl;
			return;
		}

		try {
			// Zapisujemy dane podstawowe
			file.write(reinterpret_cast<const char*>(&gameState), sizeof(gameState));

			// Zapisujemy dane gracza
			if (player != nullptr) {
				int currentHealth = player->getCurrentHealth();
				std::cout << "Zapisywanie zdrowia gracza: " << currentHealth << std::endl;
				file.write(reinterpret_cast<const char*>(&currentHealth), sizeof(currentHealth));

				float playerPosX = player->getPlayerPosition().x;
				float playerPosY = player->getPlayerPosition().y;
				file.write(reinterpret_cast<const char*>(&playerPosX), sizeof(playerPosX));
				file.write(reinterpret_cast<const char*>(&playerPosY), sizeof(playerPosY));
			}
			

			// Zapisujemy liczbê przedmiotów do zebrania
			size_t itemsCount = collectableItems.size();
			file.write(reinterpret_cast<const char*>(&itemsCount), sizeof(itemsCount));

			// Zapisujemy dane przedmiotów
			for (const auto& item : collectableItems) {
				item.save(file);
			}



			std::cout << "Stan gry zapisany do pliku: " << filename << std::endl;
		}
		catch (const std::exception& e) {
			std::cerr << "Exception during file write: " << e.what() << std::endl;
		}

		file.close();
	}

	void loadFromFile(const std::string& filename) {
		std::ifstream file(filename, std::ios::binary);  // Otwieramy plik binarnie
		if (!file.is_open()) {
			std::cerr << "Nie mo¿na otworzyæ pliku do odczytu!" << std::endl;
			return;
		}
		try {
			// Odczytujemy dane podstawowe (w tej samej kolejnoœci, co zapisano)
			file.read(reinterpret_cast<char*>(&gameState), sizeof(gameState));

			// Odczytujemy dane gracza (sprawdzamy, czy player istnieje)
			if (player != nullptr) {
				int currentHealth;
				file.read(reinterpret_cast<char*>(&currentHealth), sizeof(currentHealth));
				std::cout << "odczytywanie zdrowia gracza: " << currentHealth << std::endl;
				player->setHealth(currentHealth);

				float playerPosX, playerPosY;
				file.read(reinterpret_cast<char*>(&playerPosX), sizeof(playerPosX));
				file.read(reinterpret_cast<char*>(&playerPosY), sizeof(playerPosY));
				player->setPlayerPosition(playerPosX, playerPosY);
				std::cout << "odczytana gracza po pozycja: "
					<< playerPosX << ", "
					<< playerPosY << std::endl;
			}


			// Odczytujemy liczbê przedmiotów do zebrania
			size_t itemsCount;
			file.read(reinterpret_cast<char*>(&itemsCount), sizeof(itemsCount));

			// Odczytujemy dane przedmiotów
			collectableItems.clear();
			for (size_t i = 0; i < itemsCount; ++i) {
				CollectableItem item;
				item.load(file);  // Odczytaj dane przedmiotu z pliku
				collectableItems.push_back(item);  // Dodaj do wektora
			}



			std::cout << "Stan gry odczytany z pliku: " << filename << std::endl;
			isGameLoaded = true;
		}
		catch (const std::exception& e) {
			std::cerr << "Exception during file reading: " << e.what() << std::endl;
			isGameLoaded = false;
		}

		file.close();
	}


};

