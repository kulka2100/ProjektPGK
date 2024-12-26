#include "stdafx.h"
#include "Pause.h"

void Pause::initItems() {
	if (!playTexture.loadFromFile("textury/play.png")) {
		std::cerr << "Nie uda³o siê za³adowaæ tekstury 'play.png'!" << std::endl;
	}
	else {
		sf::Sprite sprite;
		sprite.setTexture(playTexture);
		sprite.setPosition(800 / 2.0f - 100, 600 / 2.0f);
		pauseItems.emplace_back(sprite);
	}
	if (!stopTexture.loadFromFile("textury/stop.png")) {
		std::cerr << "Nie uda³o siê za³adowaæ tekstury 'stop.png'!" << std::endl;
	}
	else {
		sf::Sprite sprite;
		sprite.setTexture(stopTexture);
		sprite.setPosition(800 / 2.0f, 600 / 2.0);
		pauseItems.emplace_back(sprite);
	}
	if (!backTexture.loadFromFile("textury/back1.png")) {
		std::cerr << "Nie uda³o siê za³adowaæ tekstury 'back1.png'!" << std::endl;
	}
	else {
		sf::Sprite sprite;
		sprite.setTexture(backTexture);
		sprite.setPosition(10.0, 20.f);
		pauseItems.emplace_back(sprite);
	}
}

Pause::Pause(float width, float height) {
	if (!font.loadFromFile("font.ttf")) {
		throw std::runtime_error("Nie mozna zaladowac czcionki");
	}
	background = new Background("textury/pause.png");
	initItems();
}

void Pause::draw(sf::RenderWindow& window) {
	background->render(window);
	for (const auto& item : pauseItems) {
		window.draw(item);
	}
}

std::vector<sf::Sprite>& Pause::getPauseItems() {
	return pauseItems;
}