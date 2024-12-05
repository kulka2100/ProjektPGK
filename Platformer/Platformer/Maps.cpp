#include "stdafx.h"
#include "Maps.h"


void Maps::initMaps(int width) {
	// �adowanie tekstur do textureManager
	textureManager.loadTexture("textury/map1.png", "map1");
	textureManager.loadTexture("textury/map2.png", "map2");
	textureManager.loadTexture("textury/map3.png", "map3");
	textureManager.loadTexture("textury/map4.png", "map4");
	textureManager.loadTexture("textury/map5.png", "map5");
	textureManager.loadTexture("textury/back.png", "back");

	// Dodanie tekstur do wektora mapsTextures
	mapsTextures = {
		*textureManager.getTexture("map1"),
		*textureManager.getTexture("map2"),
		*textureManager.getTexture("map3"),
		*textureManager.getTexture("map4"),
		*textureManager.getTexture("map5")
	};

	sf::Texture *backTexture = textureManager.getTexture("back");
	backSprite.setTexture(*backTexture);
	backSprite.setPosition(sf::Vector2f(50.f, 35.f));

	int margin = 100; // Odst�p mi�dzy elementami
	int rowHeight = 200; // Wysoko�� jednego wiersza (wysoko�� sprite'�w + odst�p)
	int colWidth = 220; // Szeroko�� jednego kolumny (szeroko�� sprite'�w + odst�p)
	int x = margin; // Pocz�tkowy margines od lewej
	int y = margin; // Pocz�tkowy margines od g�ry
	int windowWidth = width;

	// Pobieranie tekstur i tworzenie sprite
	int index = 0;
	for (const auto& texture : mapsTextures) {
		sf::Sprite sprite;
		sprite.setTexture(texture);
		// Je�li sprite wychodzi poza szeroko�� okna, przejd� do nowego wiersza
		if (x + colWidth > windowWidth) {
			x = margin; // Zresetuj pozycj� X
			y += rowHeight; // Przesu� na kolejny wiersz
		}
		sprite.setPosition(x, y); // Ustaw pozycj� sprite'a
		mapsItems.push_back(sprite);
		// Przesu� pozycj� X dla nast�pnego elementu
		x += colWidth;
	}
}


int Maps::getMapIndex(sf::RenderWindow& window) {
	for (size_t i = 0; i < mapsItems.size(); ++i) {
		if (isMouseHover(mapsItems[i], window)) {
			if (i < mapsTextures.size()) { // Sprawdzanie zakresu
				std::cout << "Zaladowano mape o indeksie: " << i << std::endl;
			}
			else {
				std::cerr << "Blad: Indeks " << i << " poza zakresem mapsTextures!" << std::endl;
			}
			return i;	//Zwraca index Kliknietego elementu
		}
	}
}


void Maps::handleHover(sf::RenderWindow& window) {
	for (auto& sprite : mapsItems) {
		// Je�li kursor jest nad sprite'em, zmie� kolor
		if (isMouseHover(sprite, window)) {
			sprite.setColor(sf::Color::Red); // Zmiana koloru na czerwony
		}
		else {
			sprite.setColor(sf::Color::White); // Przywr�� domy�lny kolor
		}
	}
	if (isMouseHover(backSprite, window)) {
		backSprite.setColor(sf::Color::Yellow);
	}
	else {
		backSprite.setColor(sf::Color(165, 42, 42));
	}
}

bool Maps::isMouseHover(const sf::Sprite& sprite, const sf::RenderWindow& window) {
	// Pobranie pozycji myszy w przestrzeni okna
	sf::Vector2i mousePos = sf::Mouse::getPosition(window);
	sf::FloatRect bounds = sprite.getGlobalBounds();

	// Sprawdzenie, czy pozycja myszy mie�ci si� w granicach sprite'a
	return bounds.contains(static_cast<sf::Vector2f>(mousePos));
}

void Maps::draw(sf::RenderWindow& window) {
	mapsBackground->render(window);
	window.draw(backSprite);
	// Rysowanie sprite'�w
	for (size_t i = 0; i < mapsItems.size(); i++) {
		window.draw(mapsItems[i]);
	}
}

