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
	}
	else {
		std::cerr << "Tekstura platforma nie zosta³a poprawnie za³adowana." << platformTexture <<std::endl;
	}
}

Game::Game(int width, int height) : width(width), height(height), isMenuActive(true){
	this->menu = new Menu(800, 600);
	this->initWindow();
	this->initPlayer();
	this->initObstacles();
	this->initBackground();
	this->initEnemies();
}

Game::~Game(){
	delete this->player;
	delete this->background;
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
				std::cout << "Gracz wyl¹dowa³ na platformie!" << std::endl;
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

void Game::updateBackground(float deltaTime, float characterSpeed){
	// Przesuñ wszystkie przeszkody o tê sam¹ wartoœæ
	if (this->background->isUpdated == true && this->background->moveRight == true) {
		for (auto& obstacle : obstacles) {
			obstacle.update(sf::Vector2f(-player->getCharacterSpeed() * deltaTime, 0));
		}
	}
	else if (this->background->isUpdated == true && this->background->moveLeft == true) {
		for (auto& obstacle : obstacles) {
			obstacle.update(sf::Vector2f(player->getCharacterSpeed() * deltaTime, 0));
		}
	}

	this->background->update(deltaTime, characterSpeed);
}

void Game::renderBackground() {
	this->background->render(this->window);
}

void Game::initEnemies() {
	this->enemies.emplace_back(sf::Vector2f(400.f, 450.f), 100.f, 0.f, 800.f);
	this->enemies.emplace_back(sf::Vector2f(600.f, 300.f), 150.f, 0.f, 800.f);
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

void Game::update() {
	// deltaTime w sekundach
	float deltaTime = clock.restart().asSeconds();
	while (this->window.pollEvent(event)) {
		if (event.type == sf::Event::Closed) {
			this->window.close();
		}

		if(isMenuActive) {
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
						isPlayed = true;
						std::cout << "Wybrano Play!\n";
						isMenuActive = false;  // Zamkniêcie menu, start gry
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


	this->updatePlayer(deltaTime);

	this->updateObstacles();

	this->updateEnemies(deltaTime);

	// T³o pod¹¿a za postaci¹
	this->updateBackground(deltaTime, player->getCharacterSpeed());
}

void Game::render() {
	this->window.clear();
	
	//render game
	if (isMenuActive) {
		// Rysuj menu, gdy jest aktywne
		menu->draw(window);
	}
	else if(isPlayed){
		// Rysowanie stanu gry, gdy menu jest wy³¹czone
		this->renderBackground();
		this->renderObstacles();
		this->renderPlayer();
		this->renderEnemies();
	}


	this->window.display();
}


