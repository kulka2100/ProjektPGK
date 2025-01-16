#include "stdafx.h"
#include "Game.h"

void Game::initWindow(){
	this->window.create(sf::VideoMode(800, 600), "Gra Platformowa", sf::Style::Default);
}

void Game::initPlayer() {
	this->player = new Player(sf::Vector2f(100.f, 400.f), 3);
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
			mapInitializer->initMap4CollectableItems(collectableItems, carrotOnTree, textureManager);
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
void Game::initEnemies(int mapIndex) {
	// Usuwanie istniej�cych przeciwnik�w (je�li s�)
	for (auto enemy : enemies) {
		delete enemy; // Zwolnienie pami�ci dla ka�dego przeciwnika
	}
	enemies.clear(); // Opr�nianie wektora
	switch (mapIndex) {
	case 0: {
	enemies.emplace_back(new Moles(sf::Vector2f(500.f, 170.f), 70.f, 500.f, 650.f));
	enemies.emplace_back(new Moles(sf::Vector2f(600.f, 390.f), 100.f, 600.f, 800.f));
	enemies.emplace_back(new Cats(sf::Vector2f(1400.f, 390.f), 150.f, 1400.f, 1700.f));
	enemies.emplace_back(new Moles(sf::Vector2f(1600, 180.f), 70.f, 1550.f, 1780));
	enemies.emplace_back(new Moles(sf::Vector2f(1700.f, 390.f), 100.f, 1700.f, 2200));
		break;
	}
	case 1: {
		enemies.emplace_back(new Moles(sf::Vector2f(500.f, 170.f), 70.f, 500.f, 650.f));
		enemies.emplace_back(new Moles(sf::Vector2f(600.f, 390.f), 100.f, 600.f, 800.f));
		enemies.emplace_back(new Cats(sf::Vector2f(1400.f, 390.f), 150.f, 1400.f, 1700.f));
		enemies.emplace_back(new Cats(sf::Vector2f(1700.f, 390.f), 150.f, 1700.f, 2200.f));

		break;
	}
	case 2: {
		enemies.emplace_back(new Moles(sf::Vector2f(500.f, 170.f), 70.f, 500.f, 650.f));
		enemies.emplace_back(new Cats(sf::Vector2f(1400.f, 390.f), 150.f, 1400.f, 1700.f));
		break;
	}
	case 3: {
		enemies.emplace_back(new Moles(sf::Vector2f(600.f, 390.f), 100.f, 600.f, 800.f));
		enemies.emplace_back(new Bats(sf::Vector2f(1600.f, 100.f), 300.f, 1300.f, 1600.f));
		enemies.emplace_back(new Boss(sf::Vector2f(2000.f, 200.f), 70.f, 2000.f, 2000.f));
		break;
	}
	case 4: {
		enemies.emplace_back(new Bats(sf::Vector2f(1600.f, 100.f), 300.f, 1300.f, 1600.f));
		enemies.emplace_back(new Bats(sf::Vector2f(600.f, 100.f), 300.f, 1300.f, 600.f));
		break;
	}
	default:
		std::cerr << "Nieobslugiwany indeks mapy : " << mapIndex << std::endl;
		break;
	}

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
	this->initEnemies(currentMap);
	this->eq = new Equipment();
	if (!font.loadFromFile("font.ttf")) {
		throw std::runtime_error("Nie mozna zaladowac czcionki");
	}
	this->statsMenu = new StatsMenu(font);
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
	delete this->statsMenu;
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
					else if (item.getType() == ItemType::Health && player->getCurrentHealth() < player->getMaxHealth()) {
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
								this->eq->setIsActive(true); // Aktywuj panel ekwipunku
							}
						}
					}
					else if (item.getType() == ItemType::Hat) {
						item.setIsCollected(true);
						eq->addItem("textury/hat.png", ItemType::Hat);
					}
					else if (item.getType() == ItemType::Wings) {
						item.setIsCollected(true);
						eq->addItem("textury/wings.png", ItemType::Wings);
					}
					else if (item.getType() == ItemType::Saw) {
						item.setIsCollected(true);
						eq->addItem("textury/saw.png", ItemType::Saw);
					}
					else if (item.getType() == ItemType::Helmet) {
						item.setIsCollected(true);
						eq->addItem("textury/helmet.png", ItemType::Helmet);
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
					else if (item.getType() == ItemType::Gate) {
						if (sf::Keyboard::isKeyPressed(sf::Keyboard::Enter)) {
							std::cout << "przeszedles do nastepnego poziomu";
							if (currentMap < 4) { // Sprawdź, czy są jeszcze mapy do odblokowania
								unlockedMaps[currentMap + 1] = true; // Odblokuj kolejną mapę
							}
							gameState = GameState::ChoosingMaps;
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

void Game::updateObstacles(float deltaTime) {
	sf::Vector2f playerPosition = player->getPlayerPosition();
	sf::FloatRect playerBounds = player->getPlayerBounds();
	// Sprawdzamy kolizj� mi�dzy graczem a ka�d� przeszkod�
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

		for (auto& obstacle : obstacles) {
			if (obstacle.getType() == ObstacleType::FallingStone) {

				obstacle.getSprite().move(0.f, 50 * deltaTime);

				if (obstacle.getSprite().getPosition().y > 700) {
					obstacle.resetPosition();
				}
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
			if (playerPosition.x + playerBounds.width > obstacleBounds.left && obstacle.getType() == ObstacleType::FallingStone) {
				if (obstacle.canDealDamage()) {
					if (!player->getWearingHelmet()) {
						player->reduceHealth(1);
					}
				}
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
			if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::E) {
				this->eq->setIsActive(true); // Aktywuj panel ekwipunku
			}
			if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::R) {
				this->eq->setIsActive(false);
			}

			if (gameState == GameState::Settings) {
				settings->handleHover(window, settings->getItems());
				if (event.type == sf::Event::MouseButtonPressed && event.mouseButton.button == sf::Mouse::Left) {
					difficultyLvel = settings->getHoverIndex(window, settings->getItems()); // Wywo�anie metody obs�ugi klikni�cia
					if (difficultyLvel == 0) {
						std::cout << "wybrano latwy" << std::endl;
						player->setHealth(5);
						player->setCurrentAmo(50);
						player->updateAmmoText(player->getCurrentAmo());
						player->updateHealthVector();
						gameState = GameState::Menu; // Zmie� stan gry na Playing po wybraniu mapy

					}
					else if (difficultyLvel == 1) {
						std::cout << "wybrano sredni" << std::endl;
						player->setCurrentAmo(20);
						player->setHealth(4);
						player->updateAmmoText(player->getCurrentAmo());
						player->updateHealthVector();
						gameState = GameState::Menu; // Zmie� stan gry na Playing po wybraniu mapy
					}
					else if (difficultyLvel == 2) {
						std::cout << "wybrano trudny" << std::endl;
						gameState = GameState::Menu; // Zmie� stan gry na Playing po wybraniu mapy
					}
					else if (difficultyLvel == 3) {
						gameState = GameState::Menu; // Zmie� stan gry na Playing po wybraniu mapy
					}
				}
			}
			if (gameState == GameState::Menu) {
				handleMenuEvents();
			}
			else if (gameState == GameState::Settings) {
				handleSettingsEvents();
			}
			else if (gameState == GameState::Playing) {
				handlePlayingEvents();
			}
			else if (gameState == GameState::ChoosingStats) {
				handleStatsMenuEvents();
			}
		}


		if (gameState == GameState::Playing) {
			updateGameplay(deltaTime);
		}

		if (gameState == GameState::Pause) {
			// Gra nie jest aktualizowana, tylko rysowanie t�a pauzy
			pause->draw(window);
			pause->handleHover(window, pause->getPauseItems());

			if (event.type == sf::Event::MouseButtonPressed && event.mouseButton.button == sf::Mouse::Left) {
				if (pause->getHoverIndex(window, pause->getPauseItems()) == 0) {
					gameState = GameState::Playing;
				}
				else if (pause->getHoverIndex(window, pause->getPauseItems()) == 1) {
					std::cout << "Saving game to file..." << std::endl;
					saveToBinaryFile("game_save.dat");
					std::cout << "Zapisano pozycj� gracza: X=" << player->getPlayerPosition().x << ", Y=" << player->getPlayerPosition().y << std::endl;

					std::cout << "Game saved successfully." << std::endl;
				}
				else if (pause->getHoverIndex(window, pause->getPauseItems()) == 2) {
					eq->resetItems();
					this->initPlayer();               // Inicjowanie postaci
					this->initObstacles(currentMap);  // Inicjowanie przeszk�d
					this->initCollectableItems(currentMap); // Inicjowanie przedmiot�w
					this->initBackground(currentMap); // Inicjowanie t�a
					this->initEnemies(currentMap);
					gameState = GameState::Menu;
				}
			}
		}


		if (gameState == GameState::ChoosingMaps) {
			maps->handleHover(window, maps->getItems());

			if (event.type == sf::Event::MouseButtonPressed && event.mouseButton.button == sf::Mouse::Left) {
				currentMap = maps->getHoverIndex(window, maps->getItems()); // Wywolanie metody obslugi klikni�cia
				if (currentMap < 5) {
					if (unlockedMaps[currentMap]) { // Sprawdź, czy mapa jest odblokowana
						gameState = GameState::Playing; // Zmien stan gry na Playing po wybraniu mapy
						this->player->setPlayerPosition(100.f, 400.f);
						initBackground(currentMap);
						initObstacles(currentMap);
						initCollectableItems(currentMap);
						initEnemies(currentMap);
					}
					else {
						// Opcjonalnie: Wyświetl komunikat, że mapa jest zablokowana
						std::cout << "Ta mapa jest jeszcze zablokowana!" << std::endl;
					}
				}
				else if (currentMap == 5) {
					gameState = GameState::Menu;
				}
			}
		}

		if (player->getIsFallen() == true) {
			eq->resetItems();
			this->initPlayer();               // Inicjowanie postaci
			this->initObstacles(currentMap);  // Inicjowanie przeszk�d
			this->initCollectableItems(currentMap); // Inicjowanie przedmiot�w
			this->initBackground(currentMap); // Inicjowanie t�a
			this->initEnemies(currentMap);
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
		// Rysowanie stanu gry, gdy menu jest wy��czone
		this->renderBackground();
		this->renderObstacles();
		this->renderCollectableItems();
		this->renderPlayer();
		this->renderEnemies();
		if (eq && eq->getIsActive()) {
			eq->render(window);
		}
		if (!font.loadFromFile("font.ttf")) {
			throw std::runtime_error("Nie mozna zaladowac czcionki");
		}
		sf::Text levelText;
		levelText.setFont(font);
		levelText.setString("\n\nLevel: " + std::to_string(player->getLevel()) + "\nExperience: " + std::to_string(player->getExperience()) + "/" + std::to_string(player->getExperienceToNext())+"\nMax Health: "+ std::to_string(player->getMaxHealth())+"\nDamage: "+std::to_string(player->getDamage())+"\nSpeed: "+std::to_string(int(player->getCharacterSpeed())));
		levelText.setCharacterSize(24);
		levelText.setFillColor(sf::Color::White);
		levelText.setPosition(10.f, 10.f);
		this->window.draw(levelText);
	}
	else if (gameState == GameState::ChoosingStats) {
		statsMenu->draw(window);
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
				(*enemyIt)->reduceHealth(player->getDamage()); // Wr�g traci �ycie
				std::cout << "Wr�g oberwal! Pozosta�o: " << (*enemyIt)->getHealth() << std::endl;

				it = this->player->getBullets().erase(it);
				//enemyHit = true;

				if ((*enemyIt)->getHealth() <= 0) {
					(*enemyIt)->startDeathAnimation();
					player->addExperience(50);
					break;
				}
			}
			else {
				++it; 
			}
		}

		if ((*enemyIt)->isDead() && (*enemyIt)->updateDeathAnimation(this->deltaTime)) {
			std::cout << "Wr�g zosta� pokonany i usuni�ty!" << std::endl;
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
			// Sprawdzanie kolizji pocisk�w bossa z graczem
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
	textureManager.loadTexture("textury/hat.png", "hat");
	textureManager.loadTexture("textury/wings.png", "wings");
	textureManager.loadTexture("textury/saw.png", "saw");
	textureManager.loadTexture("textury/helmet.png", "helmet");
	textureManager.loadTexture("textury/las/marchewka.png", "marchew");

	textureManager.loadTexture("textury/las/openchest.png", "openChest");
	textureManager.loadTexture("textury/polana/openchest.png", "openChestPolana");
	textureManager.loadTexture("textury/wulkan/openchest.png", "openChestWulkan");
	textureManager.loadTexture("textury/pieklo/openchest.png", "openChestPieklo");


	sf::Texture* openChestTexture = textureManager.getTexture("openChest");
	sf::Texture* openChestPolanaTexture = textureManager.getTexture("openChestPolana");
	sf::Texture* openChestWulkanTexture = textureManager.getTexture("openChestWulkan");
	sf::Texture* openChestPiekloTexture = textureManager.getTexture("openChestPieklo");

	sf::Texture* hatTexture = textureManager.getTexture("hat");
	sf::Texture* wingsTexture = textureManager.getTexture("wings");
	sf::Texture* sawTexture = textureManager.getTexture("saw");
	sf::Texture* helmetTexture = textureManager.getTexture("helmet");
	sf::Texture* marchewka = textureManager.getTexture("marchew");

	
	for (auto& item : collectableItems) {
		std::cout << "obecna mapa " << currentMap;
		std::cout << item.getIsChestOpen() << std::endl;
		if (item.getIsChestOpen()) {
			sf::Vector2f posChest = item.getPosition();
			std::cout << "Otwarta slkrznia" << std::endl;
			if (hatTexture && openChestTexture && currentMap == 0) {
				item.setTexture(*openChestTexture);
				item.setType(ItemType::OpenChest);
				collectableItems.emplace_back(*hatTexture, sf::Vector2f(posChest.x + 80 , posChest.y), ItemType::Hat);
				collectableItems.emplace_back(*marchewka, sf::Vector2f(posChest.x + 100, posChest.y	+ 10), ItemType::Carrot);
				collectableItems.emplace_back(*marchewka, sf::Vector2f(posChest.x + 60, posChest.y + 10), ItemType::Carrot);
				collectableItems.emplace_back(*marchewka, sf::Vector2f(posChest.x + 120, posChest.y + 10), ItemType::Carrot);
			}
			if (wingsTexture && openChestPiekloTexture && currentMap == 3) {
				item.setTexture(*openChestPiekloTexture);
				item.setType(ItemType::OpenChest);
				collectableItems.emplace_back(*wingsTexture, sf::Vector2f(posChest.x + 40, posChest.y - 20), ItemType::Wings);
				std::cout << "wings " << posChest.x << std::endl;
			}
			if (sawTexture && openChestWulkanTexture && currentMap == 2) {
				item.setTexture(*openChestWulkanTexture);
				item.setType(ItemType::OpenChest);
				collectableItems.emplace_back(*sawTexture, sf::Vector2f(posChest.x, posChest.y - 20), ItemType::Saw);
				std::cout << "wings " << posChest.x << std::endl;
			}

			if (helmetTexture && openChestPolanaTexture && currentMap == 1) {
				item.setTexture(*openChestPolanaTexture);
				item.setType(ItemType::OpenChest);
				collectableItems.emplace_back(*helmetTexture, sf::Vector2f(posChest.x, posChest.y - 20), ItemType::Helmet);
				std::cout << "wings " << posChest.x << std::endl;
			}
			
		}
	}
}

void Game::handleMenuEvents() {
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
				loadFromBinaryFile("game_save.dat");
				gameState = GameState::ChoosingMaps; // Po wczytaniu gra przechodzi do trybu rozgrywki
				isMenuActive = false;
			}

		}
	}
}

void Game::handleSettingsEvents() {
	settings->handleHover(window, settings->getItems());
	if (event.type == sf::Event::MouseButtonPressed && event.mouseButton.button == sf::Mouse::Left) {
		difficultyLvel = settings->getHoverIndex(window, settings->getItems()); // Wywolanie metody obs�ugi klikni�cia
		if (difficultyLvel == 0) {
			std::cout << "wybrano latwy" << std::endl;
			player->setHealth(5);
			player->updateAmmoText(player->getCurrentAmo());
			player->updateHealthVector();
			gameState = GameState::Menu; // Zmie� stan gry na Playing po wybraniu mapy

		}
		else if (difficultyLvel == 1) {
			std::cout << "wybrano sredni" << std::endl;
			player->setCurrentAmo(20);
			player->setHealth(4);
			player->updateAmmoText(player->getCurrentAmo());
			player->updateHealthVector();
			gameState = GameState::Menu; // Zmie� stan gry na Playing po wybraniu mapy
		}
		else if (difficultyLvel == 2) {
			std::cout << "wybrano trudny" << std::endl;
			gameState = GameState::Menu; // Zmie� stan gry na Playing po wybraniu mapy
		}
		else if (difficultyLvel == 3) {
			gameState = GameState::Menu; // Zmie� stan gry na Playing po wybraniu mapy
		}
	}
}

void Game::handlePlayingEvents() {
	if (event.type == sf::Event::KeyPressed) {
		if (event.key.code == sf::Keyboard::Escape) {
			gameState = GameState::Pause;
		}
	}

	if (player->checkLevelUp()) {
		gameState = GameState::ChoosingStats;
		std::cout << "Przej�cie do menu wyboru statystyk." << std::endl;
	}
}

void Game::handleStatsMenuEvents() {
	// Wy�wietl menu wyboru statystyki
	statsMenu->draw(window);

	if (event.type == sf::Event::KeyPressed) {
		if (event.key.code == sf::Keyboard::Up) {
			statsMenu->moveUp();
		}
		else if (event.key.code == sf::Keyboard::Down) {
			statsMenu->moveDown();
		}
		else if (event.key.code == sf::Keyboard::Enter) {
			int selectedStat = statsMenu->getSelectedIndex();
			if (selectedStat == 0) {
				player->increaseMaxHealth();
			}
			else if (selectedStat == 1) {
				player->increaseDamage();
			}
			else if (selectedStat == 2) {
				player->increaseSpeed();
			}

			std::cout << "Wybrano: " << (selectedStat == 0 ? "Zdrowie" : selectedStat == 1 ? "Obra�enia" : "Szybko��") << std::endl;
			gameState = GameState::Playing; // Powr�t do gry po wyborze
		}
	}
}

void Game::updateGameplay(float deltaTime) {
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


void Game::saveToBinaryFile(const std::string& filename) {
	std::ofstream file(filename, std::ios::binary);  // Otwieramy plik binarnie
	if (!file.is_open()) {
		std::cerr << "Nie można otworzyć pliku do zapisu!" << std::endl;
		return;
	}

	try {
		// Zapisz liczbę elementów wektora
		size_t size = unlockedMaps.size();
		file.write(reinterpret_cast<const char*>(&size), sizeof(size));

		// Zapisz elementy wektora
		for (bool unlocked : unlockedMaps) {
			file.write(reinterpret_cast<const char*>(&unlocked), sizeof(unlocked));
		}

		file.close();
	}

	catch (const std::exception& e) {
		std::cerr << "Exception during file write: " << e.what() << std::endl;
	}
}

void Game::loadFromBinaryFile(const std::string& filename) {
	std::ifstream file(filename, std::ios::binary);  // Otwieramy plik w trybie binarnym

	if (!file.is_open()) {
		std::cerr << "Nie mozna otworzyc pliku do odczytu: " << filename << std::endl;
		return;
	}

	try {
		// Odczytaj liczbe elementow wektora
		size_t size = 0;
		file.read(reinterpret_cast<char*>(&size), sizeof(size));

		// Sprawdz, czy odczytano prawidlowy rozmiar
		if (file.fail()) {
			throw std::runtime_error("Blad podczas odczytu rozmiaru wektora.");
		}

		// Odczytaj elementy wektora i przypisz je do unlockedMaps
		unlockedMaps.resize(size);
		for (size_t i = 0; i < size; ++i) {
			bool unlocked = false;
			file.read(reinterpret_cast<char*>(&unlocked), sizeof(unlocked));

			if (file.fail()) {
				throw std::runtime_error("Blad podczas odczytu elementow wektora.");
			}

			unlockedMaps[i] = unlocked;
		}

		std::cout << "Stan odblokowanych map wczytany z pliku: " << filename << std::endl;
		isGameLoaded = true;  // Ustaw flage informujaca o pomyslnym wczytaniu
	}
	catch (const std::exception& e) {
		std::cerr << "Blad podczas odczytu pliku: " << e.what() << std::endl;
		isGameLoaded = false;  // Ustaw flage informujaca o bledzie wczytywania
	}

	file.close();  // Zamknij plik
}