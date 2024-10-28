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

Game::Game(int width, int height) {
	this->width = width;
	this->height = height;
	this->menu = new Menu(800, 600);
	isMenuActive = true;

	this->initWindow();
	this->initPlayer();
	this->initBackground();
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

void Game::renderBackground() {
	this->background->render(this->window);
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

	sf::Vector2f playerPosition = player->getPlayerPosition();	
	this->updatePlayer(deltaTime);
	// T³o pod¹¿a za postaci¹
	this->background->update(deltaTime, player->getCharacterSpeed());
	
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
		this->renderPlayer();
	}



	this->window.display();
}


