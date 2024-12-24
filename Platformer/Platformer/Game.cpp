#include "stdafx.h"
#include "Game.h"

void Game::initWindow(){
	this->window.create(sf::VideoMode(800, 600), "Gra Platformowa", sf::Style::Default);
}

void Game::initPlayer() {
	this->player = new Player(sf::Vector2f(100.f, 400.f), 500.0, 3);
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
	// Wyczyœæ przeszkody przed dodaniem nowych
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
	// Usuwanie istniej¹cych przeciwników (jeœli s¹)
	for (auto enemy : enemies) {
		delete enemy; // Zwolnienie pamiêci dla ka¿dego przeciwnika
	}
	enemies.clear(); // Opró¿nianie wektora
	enemies.emplace_back(new Moles(sf::Vector2f(400.f, 170.f), 70.f, 400.f, 550.f));
	enemies.emplace_back(new Moles(sf::Vector2f(600.f, 390.f), 100.f, 600.f, 800.f));
	enemies.emplace_back(new Cats(sf::Vector2f(900.f, 390.f), 150.f, 900.f, 1200.f));
	enemies.emplace_back(new Bats(sf::Vector2f(1600.f, 100.f), 300.f, 1300.f, 1600.f));
	enemies.emplace_back(new Bats(sf::Vector2f(1300.f, 200.f), 300.f, 400.f, 600.f));
	enemies.emplace_back(new Boss(sf::Vector2f(2000.f, 200.f), 70.f, 2000.f, 2000.f));
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
	this->pause = new Pause(width, height);
	this->initEnemies();
	this->eq = new Equipment();
}

Game::~Game() {
	delete this->player;
	delete this->background;
	delete this->menu;
	delete this->pause;
	for (Enemy* enemy : enemies) {
		delete enemy;
	}
	delete eq;
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
						this->eq->addItem("textury/las/key.png", ItemType::Key);
					
					}
					else if (item.getType() == ItemType::Chest) {				
						if (player->getKeys() > 0) {
							if (sf::Keyboard::isKeyPressed(sf::Keyboard::P)) {
								item.setIsOpenChest(true);
								std::cout << "Otwarles skrzynie " << item.getIsChestOpen() << std::endl;
								setOpenChestTexture();
								this->eq->removeItem(0);
								this->eq->setIsActive(true); // Aktywuj panel ekwipunku
								
							}
						}
					}
					else if (item.getType() == ItemType::Hat) {
						item.setIsCollected(true);
						eq->addItem("textury/hat.png", ItemType::Hat);
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
	// Usuñ wszystkie zebrane przedmioty
	collectableItems.erase(
		std::remove_if(collectableItems.begin(), collectableItems.end(),
			[](const CollectableItem& item) {
				return item.getIsCollected();
			}),
		collectableItems.end());

}

void Game::updateObstacles(float deltaTime) {
	sf::Vector2f playerPosition = player->getPlayerPosition();
	sf::FloatRect playerBounds = player->getPlayerBounds();
	// Sprawdzamy kolizjê miêdzy graczem a ka¿d¹ przeszkod¹
	player->setCanMoveRight(true);
	player->setCanMoveLeft(true);
	for (auto& obstacle : obstacles) {
		sf::FloatRect obstacleBounds = obstacle.getBounds();

		if (obstacle.getType() == ObstacleType::Scythe) {
			if (moveLeftObstacle) {
				obstacle.getSprite().move(-100.0 * deltaTime, 10 * deltaTime);
			}
			if (moveRightObstacle) {
				obstacle.getSprite().move(100.0 * deltaTime, 0);
			}
			//std::cout << deltaTime << " dt" << std::endl;
			if (obstacle.getSprite().getPosition().x < 200) {
				moveRightObstacle = true;
				moveLeftObstacle = false;
			}
			else if (obstacle.getSprite().getPosition().x > 400) {
				moveRightObstacle = false;
				moveLeftObstacle = true;
			}
		}

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

			if (playerPosition.y + playerBounds.height > obstacleBounds.top &&
				playerPosition.y < obstacleBounds.top + obstacleBounds.height && obstacle.getType() == ObstacleType::Spikes) {
				if (obstacle.canDealDamage()) {
					player->reduceHealth(1);
				}
			}
			if (playerPosition.x + playerBounds.width >  obstacleBounds.left && obstacle.getType() == ObstacleType::Scythe) {
				if (obstacle.canDealDamage()) {
					player->reduceHealth(1);
				}
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

		if (gameState == GameState::Menu) {
			if (event.type == sf::Event::KeyPressed) {
				if (event.key.code == sf::Keyboard::Up) {
					menu->moveUp();
				}
				else if (event.key.code == sf::Keyboard::Down) {
					menu->moveDown();
				}
				else if (event.key.code == sf::Keyboard::Enter) {
					int selected = menu->getSelectedIndex();
					if (selected == 0) {
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
					else if (selected == 3) {
						std::cout << "Wczytywanie gry z pliku..." << std::endl;
						loadFromFile("game_save.dat");
						player->updateHealthVector();
						// Dodaj sprawdzenie poprawnoœci danych
						if (player != nullptr) {
							std::cout << "Zdrowie gracza po wczytaniu: " << player->getCurrentHealth() << std::endl;
							std::cout << "Pozycja gracza po wczytaniu: "
								<< player->getPlayerPosition().x << ", "
								<< player->getPlayerPosition().y << std::endl;
							std::cout << "Odczytano pozycjê gracza: X=" << player->getPlayerPosition().x << ", Y=" << player->getPlayerPosition().y << std::endl;

						}
						else {
							std::cerr << "B³¹d: player nie jest poprawnie zainicjalizowany!" << std::endl;
						}

						gameState = GameState::Playing; // Po wczytaniu gra przechodzi do trybu rozgrywki
						isMenuActive = false;
					}

				}
			}
		}

		if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::E) {
			this->eq->setIsActive(true); // Aktywuj panel ekwipunku
		}
		if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::R) {
			this->eq->setIsActive(false);
		}

		if (gameState == GameState::Settings) {
			settings->handleHover(window, settings->getItems());
			if (event.type == sf::Event::MouseButtonPressed && event.mouseButton.button == sf::Mouse::Left) {
				difficultyLvel = settings->getHoverIndex(window, settings->getItems()); // Wywo³anie metody obs³ugi klikniêcia
				if (difficultyLvel == 0) {
					std::cout << "wybrano latwy" << std::endl;
					loadFromFile("game_save.dat");
					player->setHealth(5);
					player->updateAmmoText(player->getCurrentAmo());
					player->updateHealthVector();
					gameState = GameState::Menu; // Zmieñ stan gry na Playing po wybraniu mapy

				}
				else if (difficultyLvel == 1) {
					std::cout << "wybrano sredni" << std::endl;
					player->setCurrentAmo(20);
					player->setHealth(4);
					player->updateAmmoText(player->getCurrentAmo());
					player->updateHealthVector();
					gameState = GameState::Menu; // Zmieñ stan gry na Playing po wybraniu mapy
				}
				else if (difficultyLvel == 2) {
					std::cout << "wybrano trudny" << std::endl;
					gameState = GameState::Menu; // Zmieñ stan gry na Playing po wybraniu mapy
				}
				else if (difficultyLvel == 3) {
					gameState = GameState::Menu; // Zmieñ stan gry na Playing po wybraniu mapy
				}
			}
		}

		if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Escape && gameState == GameState::Playing) {
			gameState = GameState::Pause;
		}
	}

	// Aktualizacja logiki gry, gdy gra jest w trybie Playing
	if (gameState == GameState::Playing) {
		this->updatePlayer(deltaTime);
		this->updateObstacles(deltaTime);
		this->updateCollectableItems(deltaTime);
		this->updateEnemies(deltaTime);
		this->checkPlayerEnemyCollision();
		this->updateBackground(deltaTime, player->getCharacterSpeed());
		this->checkBulletEnemyCollision();
		this->checkBulletPlayerCollision();
		this->checkEqPanel();
	}


	if (gameState == GameState::Pause) {
		// Gra nie jest aktualizowana, tylko rysowanie t³a pauzy
		pause->draw(window);
		pause->handleHover(window);

		if (event.type == sf::Event::MouseButtonPressed && event.mouseButton.button == sf::Mouse::Left) {
			if (pause->getPauseIndex(window) == 0) {
				gameState = GameState::Playing;
			}
			else if (pause->getPauseIndex(window) == 1) {
				std::cout << "Saving game to file..." << std::endl;
				saveToBinaryFile("game_save.dat");
				std::cout << "Zapisano pozycjê gracza: X=" << player->getPlayerPosition().x << ", Y=" << player->getPlayerPosition().y << std::endl;

				std::cout << "Game saved successfully." << std::endl;
			}
			else if (pause->getPauseIndex(window) == 2) {
				gameState = GameState::Menu;
				this->initPlayer();               // Inicjowanie postaci
				this->initObstacles(currentMap);  // Inicjowanie przeszkód
				this->initCollectableItems(currentMap); // Inicjowanie przedmiotów
				this->initBackground(currentMap); // Inicjowanie t³a
			}
		}
	}


	if (gameState == GameState::ChoosingMaps) {
		maps->handleHover(window, maps->getItems());

		if (event.type == sf::Event::MouseButtonPressed && event.mouseButton.button == sf::Mouse::Left) {
			currentMap = maps->getHoverIndex(window, maps->getItems()); // Wywo³anie metody obs³ugi klikniêcia
			if (currentMap < 5) {
				gameState = GameState::Playing; // Zmieñ stan gry na Playing po wybraniu mapy
				initBackground(currentMap);
				initObstacles(currentMap);
				initCollectableItems(currentMap);
			}
			else if (currentMap == 5) {
				gameState = GameState::Menu;
			}
		}
	}

	if (player->getIsFallen() == true) {
		this->initPlayer();               // Inicjowanie postaci
		this->initObstacles(currentMap);  // Inicjowanie przeszkód
		this->initCollectableItems(currentMap); // Inicjowanie przedmiotów
		this->initBackground(currentMap); // Inicjowanie t³a
		this->initEnemies();
		gameState = GameState::Menu;
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
		// Rysowanie stanu gry, gdy menu jest wy³¹czone
		this->renderBackground();
		this->renderObstacles();
		this->renderCollectableItems();
		this->renderPlayer();
		this->renderEnemies();
		if (eq && eq->getIsActive()) {
			eq->render(window);
		}
	}
	else if (gameState == GameState::Pause) {
		pause->draw(window);
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

				it = this->player->getBullets().erase(it);
				//enemyHit = true;

				if ((*enemyIt)->getHealth() <= 0) {
					(*enemyIt)->startDeathAnimation();
					break;
				}
			}
			else {
				++it; 
			}
		}

		if ((*enemyIt)->isDead() && (*enemyIt)->updateDeathAnimation(this->deltaTime)) {
			std::cout << "Wróg zosta³ pokonany i usuniêty!" << std::endl;
			enemyIt = this->enemies.erase(enemyIt);
		}
		else {
			++enemyIt; 
		}
	}
}

void Game::checkBulletPlayerCollision() {
	for (auto* enemy : enemies) {
		Boss* boss = dynamic_cast<Boss*>(enemy); 
		if (boss) {
			// Sprawdzanie kolizji pocisków bossa z graczem
			for (auto it = boss->getBullets().begin(); it != boss->getBullets().end(); ) {
				if (it->getBounds().intersects(player->getPlayerBounds())) { 
					player->reduceHealth(1); 
					it = boss->getBullets().erase(it); 
				}
				else {
					++it; 
				}
			}
		}
	}
}

void Game::checkEqPanel()
{
	if (eq->getIsActive()) {
		if (eq->getEqItems().empty()) {
			
		}
		else {
			this->eq->handleHover(window, eq->getEqItems());
			// Usuwanie kliknietego przedmiotu
			eq->processClick(window, *this->player);
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

	textureManager.loadTexture("textury/hat.png", "hat");
	sf::Texture* hatTexture = textureManager.getTexture("hat");

	if (openChestTexture) {
		for (auto& item : collectableItems) {

			std::cout << item.getIsChestOpen() << std::endl;
			if (item.getIsChestOpen()) {
				sf::Vector2f posChest = item.getPosition();
				std::cout << "Otwarta slkrznia" << std::endl;
				item.setTexture(*openChestTexture);
				item.setType(ItemType::OpenChest);
				if (hatTexture) {
					collectableItems.emplace_back(*hatTexture, sf::Vector2f(posChest.x + 80 , posChest.y), ItemType::Hat);
					std::cout << "dodano "  << posChest.x  << std::endl;
				}
			
			}
		}
	}
	else {
		std::cerr << "Tekstura chest nie zosta³a poprawnie za³adowana." << openChestTexture << std::endl;
	}
}
