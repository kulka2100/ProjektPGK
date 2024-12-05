#include "stdafx.h"
#include "Game.h"

void Game::initWindow(){
	this->window.create(sf::VideoMode(800, 600), "Gra Platformowa", sf::Style::Default);
}

void Game::initPlayer() {
	this->player = new Player(sf::Vector2f(100.f, 400.f), 500.0);
}

void Game::initBackground(int mapIndex) {
	switch (mapIndex) {
	case 0:
		this->background = new Background("textury/tlo3.png", this->player);
		this->background->setSpeed(200.0f);
		break;
	case 1:
		this->background = new Background("textury/tlo4.png", this->player);
		this->background->setSpeed(200.0f);
		break;
	case 2:
		this->background = new Background("textury/tlo5.png", this->player);
		this->background->setSpeed(200.0f);
		break;
	case 3:
		this->background = new Background("textury/tlo6.png", this->player);
		this->background->setSpeed(200.0f);
		break;
	case 4:
		this->background = new Background("textury/tloxd.png", this->player);
		this->background->setSpeed(200.0f);
		break;
	default:
		maps->draw(window);
		break;
	}
}

void Game::initObstacles(int mapIndex) {
	// Wyczy�� przeszkody przed dodaniem nowych
	obstacles.clear();

	switch (mapIndex) {
	case 0: {
		mapInitializer->initMap1Obstacles(obstacles, textureManager);
		break;
	}
	case 1: {
		mapInitializer->initMap2Obstacles(obstacles, textureManager);
		break;
		}
	case 2: {
		mapInitializer->initMap3Obstacles(obstacles, textureManager);
		break;
	}
	case 3: {
		mapInitializer->initMap4Obstacles(obstacles, textureManager);
		break;
	}
	case 4: {
		mapInitializer->initMap5Obstacles(obstacles, textureManager);
		break;
	}
	default:
		std::cerr << "Nieobslugiwany indeks mapy : " << mapIndex << std::endl;
		break;
	}
}

void Game::initCollectableItems(int mapIndex){
	collectableItems.clear();
	carrotOnTree.clear();
	switch (mapIndex) {
		case 0: {
			mapInitializer->initMap1CollectableItems(collectableItems,carrotOnTree, textureManager);
			break;
		}
		case 1: {
			mapInitializer->initMap2CollectableItems(collectableItems, carrotOnTree, textureManager);
			break;
		}
		case 2: {
			mapInitializer->initMap3CollectableItems(collectableItems, carrotOnTree, textureManager);
			break;
		}
		case 3: {
			break;
		}
		case 4: {
			mapInitializer->initMap5CollectableItems(collectableItems, carrotOnTree, textureManager);
			break;
		}
		default:
			std::cerr << "Nieobslugiwany indeks mapy : " << mapIndex << std::endl;
			break;
	
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
	this->menu = new Menu(width, height);
	this->maps = new Maps("textury/tloWyboru.jpg", width);
	this->settings = new Settings(width, height);
	this->initWindow();
	this->initPlayer();
	this->initObstacles(currentMap);
	this->initCollectableItems(currentMap);
	this->initBackground(currentMap);
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

	// Usu� wszystkie zebrane przedmioty
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
	// Sprawdzamy kolizj� mi�dzy graczem a ka�d� przeszkod�
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
				playerPosition.y < obstacleBounds.top + obstacleBounds.height) && obstacle.getType() == ObstacleType::Stone) {
				player->setCanMoveRight(false);
			}
			//Kolizja z prawej strony
			if ((playerBounds.left < obstacleBounds.left + obstacleBounds.width &&
				playerBounds.left + playerBounds.width > obstacleBounds.left + obstacleBounds.width &&
				playerPosition.y + playerBounds.height > obstacleBounds.top &&
				playerPosition.y < obstacleBounds.top + obstacleBounds.height) && obstacle.getType() == ObstacleType::Stone) {
				player->setCanMoveLeft(false);
			}
		}
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
	// Przesuwanie przeszk�d i wrog�w w prawo
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
						gameState = GameState::ChoosingMaps;
						isMenuActive = false;
		
					}
					else if (selected == 2) {
						std::cout << "Wybrano Settings!\n";
						gameState = GameState::Settings;
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
	
	if (gameState == GameState::ChoosingMaps) {
		maps->handleHover(window);

		if (event.type == sf::Event::MouseButtonPressed && event.mouseButton.button == sf::Mouse::Left) {
			currentMap = maps->getMapIndex(window); // Wywo�anie metody obs�ugi klikni�cia
			if (currentMap < 5) {
				gameState = GameState::Playing; // Zmie� stan gry na Playing po wybraniu mapy
				initBackground(currentMap);
				initObstacles(currentMap);
				initCollectableItems(currentMap);
			}
			else if (currentMap == 5) {
				std::cout << currentMap << " x" << std::endl;
				gameState = GameState::Menu;
			}
		}
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
	else if (gameState == GameState::ChoosingMaps) {
		maps->draw(window);
	}
	else if (gameState == GameState::Settings) {
		settings->draw(window);
	}
	else if(gameState == GameState::Playing){
		// Rysowanie stanu gry, gdy menu jest wy��czone
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
				enemy->startAttack(); // Rozpocznij animacj� ataku
				player->reduceHealth(1); // Gracz traci �ycie
				std::cout << "Gracz traci 1 �ycie! Pozosta�o: " << player->getCurrentHealth() << std::endl;
			}
		}
		else {
			enemy->resetAttack(); // Resetuj animacj�, je�li nie ma kolizji
		}
	}
}

void Game::checkBulletEnemyCollision() {
	for (auto enemyIt = this->enemies.begin(); enemyIt != this->enemies.end(); ) {
		//bool enemyHit = false;

		for (auto it = this->player->getBullets().begin(); it != this->player->getBullets().end(); ) {
			if ((*enemyIt)->getBounds().intersects(it->getBounds())) {
				(*enemyIt)->reduceHealth(1); // Wr�g traci �ycie
				std::cout << "Wr�g traci 1 �ycie! Pozosta�o: " << (*enemyIt)->getHealth() << std::endl;

				// Usu� pocisk po kolizji
				it = this->player->getBullets().erase(it);
				//enemyHit = true;

				// Je�li wr�g ginie, wyjd� z p�tli pocisk�w
				if ((*enemyIt)->getHealth() <= 0) {
					(*enemyIt)->startDeathAnimation(); // Uruchom animacj� �mierci
					break;
				}
			}
			else {
				++it; // Przejd� do nast�pnego pocisku
			}
		}

		// Je�li wr�g ma by� usuni�ty po animacji �mierci
		if ((*enemyIt)->isDead() && (*enemyIt)->updateDeathAnimation(this->deltaTime)) {
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

void Game::setOpenChestTexture() {
	textureManager.loadTexture("textury/las/openchest.png", "openChest");
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
		std::cerr << "Tekstura chest nie zosta�a poprawnie za�adowana." << openChestTexture << std::endl;
	}
}
