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
	textureManager.loadTexture("textury/kamyk.png", "kamyk");
	// Pobieranie wskaŸnika do tekstury
	sf::Texture* platformTexture = textureManager.getTexture("platforma");
	sf::Texture* kamykTexture = textureManager.getTexture("kamyk");

	if (platformTexture) {
		// Dodawanie przeszkód z za³adowan¹ tekstur¹
		obstacles.emplace_back(*platformTexture, sf::Vector2f(100, 200.f));
		obstacles.emplace_back(*platformTexture, sf::Vector2f(200.f, 340.f));
	}
	if (kamykTexture) {
		obstacles.emplace_back(*kamykTexture, sf::Vector2f(700.f, 400.0f));
		//obstacles.emplace_back(*kamykTexture, sf::Vector2f(1400.f, 400.0f));

	}
	else {
		std::cerr << "Tekstura platforma nie zosta³a poprawnie za³adowana." << platformTexture <<std::endl;
	}
}

void Game::initCollectableItems(){
	textureManager.loadTexture("textury/marchewka.png", "marchewka");
	sf::Texture* marchewkaTexture = textureManager.getTexture("marchewka");

	if (marchewkaTexture) {
		collectableItems.emplace_back(*marchewkaTexture, sf::Vector2f(400.f, 400.0f));
	}
	else {
		std::cerr << "Tekstura marchewki nie zosta³a poprawnie za³adowana." << marchewkaTexture << std::endl;
	}

}

Game::Game(int width, int height) : width(width), height(height), gameState(GameState::Menu), isMenuActive(true) {
	this->menu = new Menu(800, 600);
	this->initWindow();
	this->initPlayer();
	this->initObstacles();
	this->initCollectableItems();
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

void Game::updateCollectableItems(){
	sf::Vector2f playerPosition = player->getPlayerPosition();
	sf::FloatRect playerBounds = player->getPlayerBounds();

	for (auto& item : collectableItems) {
		sf::FloatRect itemBounds = item.getObstacleBounds();
		if (playerBounds.intersects(itemBounds)) {
			if (playerPosition.x + playerBounds.width > itemBounds.left ) {
				std::cout << "zebrales marchew" << std::endl;
				item.setIsCollected(true); // Oznacz przedmiot jako zebrany
				player->incrementCurrentAmo(); 
				player->updateAmmoText(player->getCurrentAmo());
			}
			
		}
	}
	// Usuñ wszystkie zebrane przedmioty
	collectableItems.erase(
		std::remove_if(collectableItems.begin(), collectableItems.end(),
			[](const CollectableItem& item) {
				return item.getIsCollected();
			}),
		collectableItems.end());

}

void Game::renderCollectableItems() {
	for (auto& item : collectableItems) {
		item.render(window);
	}
}

void Game::updateObstacles() {
	sf::Vector2f playerPosition = player->getPlayerPosition();
	sf::FloatRect playerBounds = player->getPlayerBounds();
	// Sprawdzamy kolizjê miêdzy graczem a ka¿d¹ przeszkod¹
	player->setCanMoveRight(true);
	player->setCanMoveLeft(true);
	for (auto& obstacle : obstacles) {
		sf::FloatRect obstacleBounds = obstacle.getObstacleBounds();

		//std::cout << "pozycja y" << playerPosition.y << " wysokosc postaci: " << playerBounds.height << std::endl;
		if (playerBounds.intersects(obstacleBounds)) {
			bool isOnPlatform = false;
			if (playerPosition.y + playerBounds.height <= obstacleBounds.top + obstacleBounds.height) {
				std::cout << playerPosition.y + playerBounds.height<<" " << obstacleBounds.top + obstacleBounds.height<< std::endl;
				player->setOnGround(true);
				isOnPlatform = true;
				player->setVerticalVelocity(0.0f);
				player->setIsJumping(false);
			}
			if ((playerPosition.x + playerBounds.width > obstacleBounds.left &&
				playerPosition.x < obstacleBounds.left &&
				playerPosition.y + playerBounds.height > obstacleBounds.top &&
				playerPosition.y < obstacleBounds.top + obstacleBounds.height)) {
				//std::cout << "Kolizja z lewej" << std::endl;
				player->setCanMoveRight(false);
			}
			if ((playerBounds.left < obstacleBounds.left + obstacleBounds.width &&
				playerBounds.left + playerBounds.width > obstacleBounds.left + obstacleBounds.width &&
				playerPosition.y + playerBounds.height > obstacleBounds.top &&
				playerPosition.y < obstacleBounds.top + obstacleBounds.height )) {
				//std::cout << "Kolizja z prawej" << std::endl;
				player->setCanMoveLeft(false);
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
		// Przesuwanie wrogów w lewo
		for (auto& enemy : this->enemies) {
			enemy.move(-player->getCharacterSpeed() * deltaTime); // Przesuwaj wrogów
		}
	}
	else if (this->background->isUpdated == true && this->background->moveLeft == true) {
		for (auto& obstacle : obstacles) {
			obstacle.update(sf::Vector2f(player->getCharacterSpeed() * deltaTime, 0));
		}
		// Przesuwanie wrogów w prawo
		for (auto& enemy : this->enemies) {
			enemy.move(player->getCharacterSpeed() * deltaTime); // Przesuwaj wrogów
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
		enemy.updateAttack(); 
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
	float deltaTime = clock.restart().asSeconds();    // Obliczanie FPS

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
		this->updateCollectableItems();
        //this->updateEnemies(deltaTime);
        this->checkPlayerEnemyCollision();
        this->updateBackground(deltaTime, player->getCharacterSpeed());
    }
}

void Game::render() {
	this->window.clear();;
	//render game
	if (gameState == GameState::Menu) {
		// Rysuj menu, gdy jest aktywne
		menu->draw(window);
	}
	else if(gameState == GameState::Playing){
		// Rysowanie stanu gry, gdy menu jest wy³¹czone
		this->renderBackground();
		this->renderObstacles();
		this->renderCollectableItems();
		this->renderPlayer();
		//this->renderEnemies();
	}

	this->window.display();
}


