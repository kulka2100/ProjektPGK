#include "stdafx.h"
#include "Game.h"

void Game::initWindow(){
	this->window.create(sf::VideoMode(800, 600), "Gra Platformowa", sf::Style::Default);
}

void Game::initPlayer() {
	this->player = new Player(sf::Vector2f(100.f, 400.f), 500.0);
}

void Game::initBackground() {
	this->background = new Background("textury/tlo3.png", this->player);
	this->background->setSpeed(200.0f);
}

void Game::initObstacles() {
	// £adowanie tekstury za pomoc¹ TextureManager
	textureManager.loadTexture("textury/platforma.png", "platforma");
	// Pobieranie wskaŸnika do tekstury
	sf::Texture* platformTexture = textureManager.getTexture("platforma");

	if (platformTexture) {
		// Dodawanie przeszkód z za³adowan¹ tekstur¹
		obstacles.emplace_back(*platformTexture, sf::Vector2f(100, 150.f));
		obstacles.emplace_back(*platformTexture, sf::Vector2f(200.f, 340.f));
		obstacles.emplace_back(*platformTexture, sf::Vector2f(400.f, 250.f));
	}
	else {
		std::cerr << "Tekstura platforma nie zosta³a poprawnie za³adowana." << platformTexture <<std::endl;
	}
}

Game::Game(int width, int height) : width(width), height(height), gameState(GameState::Menu), isMenuActive(true) {
	this->menu = new Menu(800, 600);
	this->initWindow();
	this->initPlayer();
	this->initObstacles();
	this->initBackground();
	this->initEnemies();
}

Game::~Game() {
	delete this->player;
	delete this->background;
	delete this->menu;
}

sf::RenderWindow& Game::getWindow() {
	return this->window;
}

void Game::updatePlayer(float deltaTime) {
	this->player->update(deltaTime, event);
}

void Game::renderPlayer() {
	this->player->render(this->window);
}

void Game::updateObstacles() {
	sf::Vector2f playerPosition = player->getPlayerPosition();
	// Sprawdzamy kolizjê miêdzy graczem a ka¿d¹ przeszkod¹
	for (auto& obstacle : obstacles) {
		bool isOnPlatform = false;
		if (player->getPlayerBounds().intersects(obstacle.getObstacleBounds())) {
			if (playerPosition.y + player->getPlayerBounds().height <= obstacle.getObstaclePosition().y + 10.f) {
				player->getPlayerSprite().setPosition(player->getPlayerPosition().x, obstacle.getObstaclePosition().y - player->getPlayerBounds().height);
				player->setOnGround(true);
				isOnPlatform = true;
				player->setVerticalVelocity(0.0f);
				player->setIsJumping(false);
			}
		}
	}
}

void Game::renderObstacles() {
	for (auto& obstacle : obstacles) {
		obstacle.render(window);
	}
}

void Game::updateBackground(float deltaTime, float characterSpeed) {
	float offset = player->getCharacterSpeed() * deltaTime;

	// Przesuwanie przeszkód i wrogów w lewo
	if (this->background->isUpdated == true && this->background->moveRight == true) {
		for (auto& obstacle : obstacles) {
			obstacle.update(sf::Vector2f(-offset, 0));
		}
		for (auto& enemy : this->enemies) {
			enemy.move(-offset); // Przesuwanie pozycji wroga
			enemy.setBoundaries(enemy.getLeftBoundary() - offset, enemy.getRightBoundary() - offset);
		}
	}
	// Przesuwanie przeszkód i wrogów w prawo
	else if (this->background->isUpdated == true && this->background->moveLeft == true) {
		for (auto& obstacle : obstacles) {
			obstacle.update(sf::Vector2f(offset, 0));
		}
		for (auto& enemy : this->enemies) {
			enemy.move(offset); // Przesuwanie pozycji wroga
			enemy.setBoundaries(enemy.getLeftBoundary() + offset, enemy.getRightBoundary() + offset);
		}
	}

	this->background->update(deltaTime, characterSpeed);
}

void Game::renderBackground() {
	this->background->render(this->window);
}

void Game::initEnemies() {
	this->enemies.emplace_back(sf::Vector2f(400.f, 170.f), 100.f, 400.f, 550.f);
	this->enemies.emplace_back(sf::Vector2f(600.f, 390.f), 150.f, 600.f, 800.f);
}

void Game::updateEnemies(float deltaTime) {
	for (auto& enemy : this->enemies) {
		enemy.update(deltaTime);
	}
}

void Game::renderEnemies() {
	for (auto& enemy : this->enemies) {
		enemy.render(this->window);
	}
}

void Game::checkPlayerEnemyCollision() {
	for (auto& enemy : this->enemies) {
		if (player->getPlayerBounds().intersects(enemy.getBounds())) {
			if (enemy.canDealDamage()) {
				enemy.startAttack(); // Rozpocznij animacjê ataku
				player->reduceHealth(1); // Gracz traci ¿ycie
				std::cout << "Gracz traci 1 ¿ycie! Pozosta³o: " << player->getHealth() << std::endl;
			}
		}
		else {
			enemy.resetAttack(); // Resetuj animacjê, jeœli nie ma kolizji
		}
	}
}

void Game::update() {
	// deltaTime w sekundach
	float deltaTime = clock.restart().asSeconds();
	while (this->window.pollEvent(event)) {
		if (event.type == sf::Event::Closed) {
			this->window.close();
		}

		if(gameState == GameState::Menu) {
			if (event.type == sf::Event::KeyPressed) {
				if (event.key.code == sf::Keyboard::Up) {
					menu->moveUp();
				}
				else if (event.key.code == sf::Keyboard::Down) {
					menu->moveDown();
				}
				else if (event.key.code == sf::Keyboard::Enter) {
					int selected = menu->getSelectedIndex();
					if(selected == 0) {
						// Play
						gameState = GameState::Playing;
						std::cout << "Wybrano Play!\n";
						isMenuActive = false;
					}
					else if (selected == 1) {
						std::cout << "Wybrano Maps!\n";
						isMenuActive = false;
		
					}
					else if (selected == 2) {
						std::cout << "Wybrano Settings!\n";
						isMenuActive = false;
					}
				}
			}
		}
	}
	// Aktualizacja logiki gry, gdy gra jest w trybie Playing
    if (gameState == GameState::Playing) {
        this->updatePlayer(deltaTime);
        this->updateObstacles();
        this->updateEnemies(deltaTime);
        this->checkPlayerEnemyCollision();
        this->updateBackground(deltaTime, player->getCharacterSpeed());
		this->checkBulletEnemyCollision();
    }
}

void Game::render() {
	this->window.clear();
	
	//render game
	if (gameState == GameState::Menu) {
		// Rysuj menu, gdy jest aktywne
		menu->draw(window);
	}
	else if(gameState == GameState::Playing){
		// Rysowanie stanu gry, gdy menu jest wy³¹czone
		this->renderBackground();
		this->renderObstacles();
		this->renderPlayer();
		this->renderEnemies();
	}


	this->window.display();
}

void Game::checkBulletEnemyCollision() {
	for (auto enemyIt = this->enemies.begin(); enemyIt != this->enemies.end(); ) {
		//bool enemyHit = false;

		for (auto it = this->player->getBullets().begin(); it != this->player->getBullets().end(); ) {
			if (enemyIt->getBounds().intersects(it->getBounds())) {
				enemyIt->reduceHealth(1); // Wróg traci ¿ycie
				std::cout << "Wróg traci 1 ¿ycie! Pozosta³o: " << enemyIt->getHealth() << std::endl;

				// Usuñ pocisk po kolizji
				it = this->player->getBullets().erase(it);
				//enemyHit = true;

				// Jeœli wróg ginie, wyjdŸ z pêtli pocisków
				if (enemyIt->getHealth() <= 0) {
					enemyIt->startDeathAnimation(); // Uruchom animacjê œmierci
					break;
				}
			}
			else {
				++it; // PrzejdŸ do nastêpnego pocisku
			}
		}

		// Jeœli wróg ma byæ usuniêty po animacji œmierci
		if (enemyIt->isDead() && enemyIt->updateDeathAnimation(this->deltaTime)) {
			std::cout << "Wróg zosta³ pokonany i usuniêty!" << std::endl;
			enemyIt = this->enemies.erase(enemyIt);
		}
		else {
			++enemyIt; // PrzejdŸ do nastêpnego wroga
		}
	}
}

void Game::updateDeltaTime() {
	static sf::Clock clock;
	this->deltaTime = clock.restart().asSeconds();
}