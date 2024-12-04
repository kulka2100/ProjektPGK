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
	textureManager.loadTexture("textury/malaPlatforma.png", "malaPlatforma");
	textureManager.loadTexture("textury/kamyk.png", "kamyk");
	// Pobieranie wskaŸnika do tekstury
	sf::Texture* platformTexture = textureManager.getTexture("platforma");
	sf::Texture* smallPlatformTexture = textureManager.getTexture("malaPlatforma");
	sf::Texture* kamykTexture = textureManager.getTexture("kamyk");

	if (platformTexture) {
		// Dodawanie przeszkód z za³adowan¹ tekstur¹
		obstacles.emplace_back(*platformTexture, sf::Vector2f(50, 200.f));
		obstacles.emplace_back(*platformTexture, sf::Vector2f(500.f, 250.f));
	}
	if (kamykTexture) {
		obstacles.emplace_back(*kamykTexture, sf::Vector2f(700.f, 400.0f));
	}
	else {
		std::cerr << "Tekstura platforma nie zosta³a poprawnie za³adowana." << platformTexture <<std::endl;
	}
	if (smallPlatformTexture) {
		obstacles.emplace_back(*smallPlatformTexture, sf::Vector2f(250.f, 380.f));
	}
}

void Game::initCollectableItems(){
	textureManager.loadTexture("textury/marchewka.png", "marchewka");
	textureManager.loadTexture("textury/hp.png", "health");
	textureManager.loadTexture("textury/key.png", "key");
	textureManager.loadTexture("textury/chest.png", "chest");
	textureManager.loadTexture("textury/tree.png", "tree");

	sf::Texture* marchewkaTexture = textureManager.getTexture("marchewka");
	sf::Texture* healthTexture = textureManager.getTexture("health");
	sf::Texture* keyTexture = textureManager.getTexture("key");
	sf::Texture* chestTexture = textureManager.getTexture("chest");
	sf::Texture* treeTexture = textureManager.getTexture("tree");


	if (marchewkaTexture) {
		collectableItems.emplace_back(*marchewkaTexture, sf::Vector2f(400.f, 400.0f), ItemType::Carrot);
		collectableItems.emplace_back(*marchewkaTexture, sf::Vector2f(200.f, 400.0f), ItemType::Carrot);
		collectableItems.emplace_back(*marchewkaTexture, sf::Vector2f(1400.f, 170.f), ItemType::Carrot);
	}
	else {
		std::cerr << "Tekstura marchewki nie zosta³a poprawnie za³adowana." << marchewkaTexture << std::endl;
	}
	if (healthTexture) {
		collectableItems.emplace_back(*healthTexture, sf::Vector2f(400.f, 230.f), ItemType::Health);
		collectableItems.emplace_back(*healthTexture, sf::Vector2f(200.f, 230.f), ItemType::Health);
	}
	else {
		std::cerr << "Tekstura hp nie zosta³a poprawnie za³adowana." << healthTexture << std::endl;
	}
	if (keyTexture) {
		collectableItems.emplace_back(*keyTexture, sf::Vector2f(750.f, 330.f), ItemType::Key);
	}
	else {
		std::cerr << "Tekstura key nie zosta³a poprawnie za³adowana." << keyTexture << std::endl;
	}

	if (chestTexture) {
		collectableItems.emplace_back(*chestTexture, sf::Vector2f(1300.f, 330.f), ItemType::Chest);
	}
	else {
		std::cerr << "Tekstura chest nie zosta³a poprawnie za³adowana." << chestTexture << std::endl;
	}

	if (treeTexture && marchewkaTexture) {
		collectableItems.emplace_back(*treeTexture, sf::Vector2f(1000.f, 150.f), ItemType::Tree);
		// Uzyskanie referencji do ostatnio dodanego elementu (drzewa)
		carrotOnTree.emplace_back(*marchewkaTexture, sf::Vector2f(1100.f, 170.f), ItemType::Carrot);
		carrotOnTree.emplace_back(*marchewkaTexture, sf::Vector2f(1100.f, 270.f), ItemType::Carrot);
		carrotOnTree.emplace_back(*marchewkaTexture, sf::Vector2f(1200.f, 200.f), ItemType::Carrot);
	}
	else {
		std::cerr << "Tekstura chest nie zosta³a poprawnie za³adowana." << treeTexture << std::endl;
	}


}

void Game::initEnemies() {
	enemies.emplace_back(new Moles(sf::Vector2f(400.f, 170.f), 70.f, 400.f, 550.f));
	enemies.emplace_back(new Moles(sf::Vector2f(600.f, 390.f), 100.f, 600.f, 800.f));
	enemies.emplace_back(new Cats(sf::Vector2f(900.f, 390.f), 150.f, 900.f, 1200.f));
	enemies.emplace_back(new Bats(sf::Vector2f(1600.f, 100.f), 300.f, 1300.f, 1600.f));
	enemies.emplace_back(new Bats(sf::Vector2f(1300.f, 200.f), 300.f, 400.f, 600.f));
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
	for (Enemy* enemy : enemies) {
		delete enemy;
	}
	enemies.clear();
}

sf::RenderWindow& Game::getWindow() {
	return this->window;
}

void Game::updatePlayer(float deltaTime) {
	this->player->update(deltaTime, event);
}

void Game::updateCollectableItems(float deltaTime){
	sf::Vector2f playerPosition = player->getPlayerPosition();
	sf::FloatRect playerBounds = player->getPlayerBounds();
	int keysCounter = 0;

	for (auto& item : collectableItems) {
		sf::FloatRect itemBounds = item.getBounds();
			if (playerBounds.intersects(itemBounds)) {
				if (playerPosition.x + playerBounds.width > itemBounds.left) {
					if (item.getType() == ItemType::Carrot) {
						std::cout << "zebrales marchew" << std::endl;
						item.setIsCollected(true); // Oznacz przedmiot jako zebrany
						player->incrementCurrentAmo();
						player->updateAmmoText(player->getCurrentAmo());
					}
					else if (item.getType() == ItemType::Health) {
						std::cout << "zebrales zycie" << std::endl;
						item.setIsCollected(true);
						player->updateHealth();
						std::cout << player->getCurrentHealth() << std::endl;

					}
					else if (item.getType() == ItemType::Key) {
						std::cout << "zebrales klucz" << std::endl;
						keysCounter++;
						player->setKeys(keysCounter);
						item.setIsCollected(true);
					}
					else if (item.getType() == ItemType::Chest) {				
						if (player->getKeys() > 0) {
							if (sf::Keyboard::isKeyPressed(sf::Keyboard::P)) {
								item.setIsOpenChest(true);
								std::cout << "Otwarles skrzynie " << item.getIsChestOpen() << std::endl;
								setOpenChestTexture();
							}
						}
					}
					else if (item.getType() == ItemType::Tree) {
						if (sf::Keyboard::isKeyPressed(sf::Keyboard::L)) {
							std::cout << "wcisnieto l" << std::endl;
							for (auto& carot : carrotOnTree) {
								if (carot.getType() == ItemType::Carrot) {
									carot.getSprite().move(0, 200.f * deltaTime);
									carot.setIsCollected(true);
								}
							}
						}
					}
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

void Game::updateObstacles() {
	sf::Vector2f playerPosition = player->getPlayerPosition();
	sf::FloatRect playerBounds = player->getPlayerBounds();
	// Sprawdzamy kolizjê miêdzy graczem a ka¿d¹ przeszkod¹
	player->setCanMoveRight(true);
	player->setCanMoveLeft(true);
	for (auto& obstacle : obstacles) {
		sf::FloatRect obstacleBounds = obstacle.getBounds();

		if (playerBounds.intersects(obstacleBounds)) {
			bool isOnPlatform = false;
			//Kolizja z gory
			if (playerPosition.y + playerBounds.height <= obstacleBounds.top + obstacleBounds.height) {
				player->setOnGround(true);
				isOnPlatform = true;
				player->setVerticalVelocity(0.0f);
				player->setIsJumping(false);
			}
			//Kolizja z lewej strony
			if ((playerPosition.x + playerBounds.width > obstacleBounds.left &&
				playerPosition.x < obstacleBounds.left &&
				playerPosition.y + playerBounds.height > obstacleBounds.top &&
				playerPosition.y < obstacleBounds.top + obstacleBounds.height)) {
				player->setCanMoveRight(false);
			}
			//Kolizja z prawej strony
			if ((playerBounds.left < obstacleBounds.left + obstacleBounds.width &&
				playerBounds.left + playerBounds.width > obstacleBounds.left + obstacleBounds.width &&
				playerPosition.y + playerBounds.height > obstacleBounds.top &&
				playerPosition.y < obstacleBounds.top + obstacleBounds.height )) {
				player->setCanMoveLeft(false);
			}
		}
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
			enemy->move(-offset); // Przesuwanie pozycji wroga
			enemy->setBoundaries(enemy->getLeftBoundary() - offset, enemy->getRightBoundary() - offset);
		}
		for (auto& item : this->collectableItems) {
			item.update(sf::Vector2f(-offset, 0));
		}
		for (auto& item : this->carrotOnTree) {
			item.update(sf::Vector2f(-offset, 0));
		}
	}
	// Przesuwanie przeszkód i wrogów w prawo
	else if (this->background->isUpdated == true && this->background->moveLeft == true) {
		for (auto& obstacle : obstacles) {
			obstacle.update(sf::Vector2f(offset, 0));
		}
		for (auto& enemy : this->enemies) {
			enemy->move(offset); // Przesuwanie pozycji wroga
			enemy->setBoundaries(enemy->getLeftBoundary() + offset, enemy->getRightBoundary() + offset);
		}
		for (auto& item : collectableItems) {
			item.update(sf::Vector2f(offset, 0));
		}
		for (auto& item: carrotOnTree) {
			item.update(sf::Vector2f(offset, 0));
		}
	}

	this->background->update(deltaTime, characterSpeed);
}

void Game::updateEnemies(float deltaTime) {
	for (auto& enemy : this->enemies) {
		enemy->update(deltaTime);
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
						std::cout << "Wybrano Play!\n" << std::endl;
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
		this->updateCollectableItems(deltaTime);
        this->updateEnemies(deltaTime);
        this->checkPlayerEnemyCollision();
        this->updateBackground(deltaTime, player->getCharacterSpeed());
		this->checkBulletEnemyCollision();
    }
}



void Game::renderBackground() {
	this->background->render(this->window);
}

void Game::renderEnemies() {
	for (auto& enemy : this->enemies) {
		enemy->render(this->window);
	}
}

void Game::renderObstacles() {
	for (auto& obstacle : obstacles) {
		obstacle.render(window);
	}
}

void Game::renderCollectableItems() {

	for (auto& carrot : carrotOnTree) {
		carrot.render(window);
	}

	for (auto& item : collectableItems) {
		item.render(window);
	}

}

void Game::renderPlayer() {
	this->player->render(this->window);
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
		this->renderEnemies();
	}

	this->window.display();
}

void Game::checkPlayerEnemyCollision() {
	for (auto& enemy : this->enemies) {
		if (player->getPlayerBounds().intersects(enemy->getBounds())) {
			if (enemy->canDealDamage()) {
				enemy->startAttack(); // Rozpocznij animacjê ataku
				player->reduceHealth(1); // Gracz traci ¿ycie
				std::cout << "Gracz traci 1 ¿ycie! Pozosta³o: " << player->getCurrentHealth() << std::endl;
			}
		}
		else {
			enemy->resetAttack(); // Resetuj animacjê, jeœli nie ma kolizji
		}
	}
}

void Game::checkBulletEnemyCollision() {
	for (auto enemyIt = this->enemies.begin(); enemyIt != this->enemies.end(); ) {
		//bool enemyHit = false;

		for (auto it = this->player->getBullets().begin(); it != this->player->getBullets().end(); ) {
			if ((*enemyIt)->getBounds().intersects(it->getBounds())) {
				(*enemyIt)->reduceHealth(1); // Wróg traci ¿ycie
				std::cout << "Wróg traci 1 ¿ycie! Pozosta³o: " << (*enemyIt)->getHealth() << std::endl;

				// Usuñ pocisk po kolizji
				it = this->player->getBullets().erase(it);
				//enemyHit = true;

				// Jeœli wróg ginie, wyjdŸ z pêtli pocisków
				if ((*enemyIt)->getHealth() <= 0) {
					(*enemyIt)->startDeathAnimation(); // Uruchom animacjê œmierci
					break;
				}
			}
			else {
				++it; // PrzejdŸ do nastêpnego pocisku
			}
		}

		// Jeœli wróg ma byæ usuniêty po animacji œmierci
		if ((*enemyIt)->isDead() && (*enemyIt)->updateDeathAnimation(this->deltaTime)) {
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

void Game::setOpenChestTexture() {
	textureManager.loadTexture("textury/openchest.png", "openChest");
	sf::Texture* openChestTexture = textureManager.getTexture("openChest");

	if (openChestTexture) {
		//collectableItems.emplace_back(*openChestTexture, sf::Vector2f(1800.f, 400.f), ItemType::OpenChest);
		for (auto& item : collectableItems) {
			std::cout << item.getIsChestOpen() << std::endl;
			if (item.getIsChestOpen()) {
				std::cout << "Otwarta slkrznia" << std::endl;
				item.setTexture(*openChestTexture);
				item.setType(ItemType::OpenChest);
			}
		}
	}
	else {
		std::cerr << "Tekstura chest nie zosta³a poprawnie za³adowana." << openChestTexture << std::endl;
	}
}
