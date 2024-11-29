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
	// �adowanie tekstury za pomoc� TextureManager
	textureManager.loadTexture("textury/platforma.png", "platforma");
	textureManager.loadTexture("textury/kamyk.png", "kamyk");
	// Pobieranie wska�nika do tekstury
	sf::Texture* platformTexture = textureManager.getTexture("platforma");
	sf::Texture* kamykTexture = textureManager.getTexture("kamyk");

	if (platformTexture) {
		// Dodawanie przeszk�d z za�adowan� tekstur�
		obstacles.emplace_back(*platformTexture, sf::Vector2f(100, 200.f));
		obstacles.emplace_back(*platformTexture, sf::Vector2f(200.f, 340.f));
		obstacles.emplace_back(*platformTexture, sf::Vector2f(400.f, 250.f));
	}
	if (kamykTexture) {
		obstacles.emplace_back(*kamykTexture, sf::Vector2f(700.f, 400.0f));
		//obstacles.emplace_back(*kamykTexture, sf::Vector2f(1400.f, 400.0f));

	}
	else {
		std::cerr << "Tekstura platforma nie zosta�a poprawnie za�adowana." << platformTexture <<std::endl;
	}
}

void Game::initCollectableItems(){
	textureManager.loadTexture("textury/marchewka.png", "marchewka");
	sf::Texture* marchewkaTexture = textureManager.getTexture("marchewka");

	if (marchewkaTexture) {
		collectableItems.emplace_back(*marchewkaTexture, sf::Vector2f(400.f, 400.0f));
	}
	else {
		std::cerr << "Tekstura marchewki nie zosta�a poprawnie za�adowana." << marchewkaTexture << std::endl;
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
	// Usu� wszystkie zebrane przedmioty
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
	// Sprawdzamy kolizj� mi�dzy graczem a ka�d� przeszkod�
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

void Game::updateBackground(float deltaTime, float characterSpeed) {
	float offset = player->getCharacterSpeed() * deltaTime;

	// Przesuwanie przeszk�d i wrog�w w lewo
	if (this->background->isUpdated == true && this->background->moveRight == true) {
		for (auto& obstacle : obstacles) {
			obstacle.update(sf::Vector2f(-offset, 0));
		}
		for (auto& enemy : this->enemies) {
			enemy.move(-offset); // Przesuwanie pozycji wroga
			enemy.setBoundaries(enemy.getLeftBoundary() - offset, enemy.getRightBoundary() - offset);
		}
	}
	// Przesuwanie przeszk�d i wrog�w w prawo
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
				enemy.startAttack(); // Rozpocznij animacj� ataku
				player->reduceHealth(1); // Gracz traci �ycie
				std::cout << "Gracz traci 1 �ycie! Pozosta�o: " << player->getHealth() << std::endl;
			}
		}
		else {
			enemy.resetAttack(); // Resetuj animacj�, je�li nie ma kolizji
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
		this->checkBulletEnemyCollision();
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
		// Rysowanie stanu gry, gdy menu jest wy��czone
		this->renderBackground();
		this->renderObstacles();
		this->renderCollectableItems();
		this->renderPlayer();
		//this->renderEnemies();
	}

	this->window.display();
}

void Game::checkBulletEnemyCollision() {
	for (auto enemyIt = this->enemies.begin(); enemyIt != this->enemies.end(); ) {
		//bool enemyHit = false;

		for (auto it = this->player->getBullets().begin(); it != this->player->getBullets().end(); ) {
			if (enemyIt->getBounds().intersects(it->getBounds())) {
				enemyIt->reduceHealth(1); // Wr�g traci �ycie
				std::cout << "Wr�g traci 1 �ycie! Pozosta�o: " << enemyIt->getHealth() << std::endl;

				// Usu� pocisk po kolizji
				it = this->player->getBullets().erase(it);
				//enemyHit = true;

				// Je�li wr�g ginie, wyjd� z p�tli pocisk�w
				if (enemyIt->getHealth() <= 0) {
					enemyIt->startDeathAnimation(); // Uruchom animacj� �mierci
					break;
				}
			}
			else {
				++it; // Przejd� do nast�pnego pocisku
			}
		}

		// Je�li wr�g ma by� usuni�ty po animacji �mierci
		if (enemyIt->isDead() && enemyIt->updateDeathAnimation(this->deltaTime)) {
			std::cout << "Wr�g zosta� pokonany i usuni�ty!" << std::endl;
			enemyIt = this->enemies.erase(enemyIt);
		}
		else {
			++enemyIt; // Przejd� do nast�pnego wroga
		}
	}
}

void Game::updateDeltaTime() {
	static sf::Clock clock;
	this->deltaTime = clock.restart().asSeconds();
}