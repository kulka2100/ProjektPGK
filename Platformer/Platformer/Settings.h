#pragma once
#include "Menu.h"
#include "TextureManager.h"

class Settings : public Menu
{
private:
	std::vector <sf::Sprite> settingsItems;
	std::vector <sf::Texture> settingsTextures;
	sf::Sprite backSprite;
	Background* mapsBackground;
	TextureManager textureManager;

public:
	Settings(float width, float height) {
		// £adowanie tekstur do textureManager
		textureManager.loadTexture("textury/easy.png", "easy");
		textureManager.loadTexture("textury/medium.png", "medium");
		textureManager.loadTexture("textury/hard.png", "hard");
		textureManager.loadTexture("textury/back.png", "back");

		settingsTextures = {
		*textureManager.getTexture("easy"),
		*textureManager.getTexture("medium"),
		*textureManager.getTexture("hard"),
		};

		sf::Texture* backTexture = textureManager.getTexture("back");
		if (backTexture) {
			backSprite.setTexture(*backTexture);
			backSprite.setPosition(sf::Vector2f(50.f, 35.f));
		}

        background = new Background("textury/settings.png");


		float margin = 20.0f;  // Margines pomiêdzy sprite'ami
		float totalHeight = settingsTextures.size() * settingsTextures[0].getSize().y + (settingsTextures.size() - 1) * margin; // Ca³kowita wysokoœæ z marginesami

		float startY = (height - totalHeight) / 2.0f; // Pocz¹tkowa Y, aby wycentrowaæ na osi Y

		for (const auto& texture : settingsTextures) {
			sf::Sprite sprite;
			sprite.setTexture(texture);

			// Ustawianie pozycji X, aby wycentrowaæ na szerokoœci okna
			float startX = width / 2.0f - sprite.getGlobalBounds().width / 2.0f;

			// Ustawianie pozycji Y z zachowaniem marginesów
			sprite.setPosition(sf::Vector2f(startX + 18.f , startY + 30.f));

			// Dodawanie sprite'a do kontenera
			settingsItems.push_back(sprite);

			// Zwiêkszanie pozycji Y dla kolejnego sprite'a z uwzglêdnieniem marginesu
			startY += sprite.getGlobalBounds().height + margin;
		}
	}



	int getLevelIndex(sf::RenderWindow& window) {
		for (size_t i = 0; i < settingsItems.size(); ++i) {
			if (isMouseHover(settingsItems[i], window)) {
				if (i < settingsItems.size()) { // Sprawdzanie zakresu
					std::cout << "Zaladowano mape o indeksie: " << i << std::endl;
				}
				else {
					std::cerr << "Blad: Indeks " << i << " poza zakresem mapsTextures!" << std::endl;
				}
				return i;	//Zwraca index Kliknietego elementu
			}
		}
	}


	void handleHover(sf::RenderWindow& window) {
		for (auto& sprite : settingsItems) {
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



	void draw(sf::RenderWindow& window) {
		background->render(window);
		window.draw(backSprite);
		for (const auto& item : settingsItems) {
			window.draw(item);
		}
	}
};

