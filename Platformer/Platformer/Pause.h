#pragma once
#include "stdafx.h"
#include "Background.h"
#include "TextureManager.h"

class Pause
{
private:
	sf::Font font;
	Background* background;
	sf::Texture playTexture;
	sf::Texture stopTexture;
	sf::Sprite backSprite;
	sf::Texture backTexture;
	std::vector<sf::Sprite> pauseItems;

	void initItems() {
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


public:
	Pause(float width, float height) {
		if (!font.loadFromFile("font.ttf")) {
			throw std::runtime_error("Nie mozna zaladowac czcionki");
		}
		background = new Background("textury/pause.png");
		initItems();
	}
	~Pause() {
		delete background;
	}


	void handleHover(sf::RenderWindow& window) {
		for (auto& sprite : pauseItems) {
			// Jeœli kursor jest nad sprite'em, zmieñ kolor
			if (isMouseHover(sprite, window)) {
				sprite.setColor(sf::Color::Red); // Zmiana koloru na czerwony
			}
			else {
				sprite.setColor(sf::Color::White); // Przywróæ domyœlny kolor
			}
		}
		if (isMouseHover(backSprite, window)) {
			backSprite.setColor(sf::Color::Yellow);
		}
		else {
			backSprite.setColor(sf::Color(165, 42, 42));
		}
	}

	bool isMouseHover(const sf::Sprite& sprite, const sf::RenderWindow& window) {
		// Pobranie pozycji myszy w przestrzeni okna
		sf::Vector2i mousePos = sf::Mouse::getPosition(window);
		sf::FloatRect bounds = sprite.getGlobalBounds();

		// Sprawdzenie, czy pozycja myszy mieœci siê w granicach sprite'a
		return bounds.contains(static_cast<sf::Vector2f>(mousePos));
	}




	int getPauseIndex(sf::RenderWindow& window) {
		for (size_t i = 0; i < pauseItems.size(); ++i) {
			if (isMouseHover(pauseItems[i], window)) {
				if (i < pauseItems.size()) { // Sprawdzanie zakresu
					std::cout << "Wcisnieto sprite indeksie: " << i << std::endl;
				}
				else {
					std::cerr << "Blad: Indeks " << i << " poza zakresem!" << std::endl;
				}
				return i;	//Zwraca index Kliknietego elementu
			}
		}
	}


	void draw(sf::RenderWindow& window) {
		background->render(window);
		for (const auto& item : pauseItems) {
			window.draw(item);
		}
	}


};

