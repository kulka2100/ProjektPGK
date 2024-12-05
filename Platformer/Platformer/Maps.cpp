#include "stdafx.h"
#include "Maps.h"


void Maps::initMaps(int width) {
	// £adowanie tekstur do textureManager
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

	int margin = 100; // Odstêp miêdzy elementami
	int rowHeight = 200; // Wysokoœæ jednego wiersza (wysokoœæ sprite'ów + odstêp)
	int colWidth = 220; // Szerokoœæ jednego kolumny (szerokoœæ sprite'ów + odstêp)
	int x = margin; // Pocz¹tkowy margines od lewej
	int y = margin; // Pocz¹tkowy margines od góry
	int windowWidth = width;

	// Pobieranie tekstur i tworzenie sprite
	int index = 0;
	for (const auto& texture : mapsTextures) {
		sf::Sprite sprite;
		sprite.setTexture(texture);
		// Jeœli sprite wychodzi poza szerokoœæ okna, przejdŸ do nowego wiersza
		if (x + colWidth > windowWidth) {
			x = margin; // Zresetuj pozycjê X
			y += rowHeight; // Przesuñ na kolejny wiersz
		}
		sprite.setPosition(x, y); // Ustaw pozycjê sprite'a
		mapsItems.push_back(sprite);
		// Przesuñ pozycjê X dla nastêpnego elementu
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

bool Maps::isMouseHover(const sf::Sprite& sprite, const sf::RenderWindow& window) {
	// Pobranie pozycji myszy w przestrzeni okna
	sf::Vector2i mousePos = sf::Mouse::getPosition(window);
	sf::FloatRect bounds = sprite.getGlobalBounds();

	// Sprawdzenie, czy pozycja myszy mieœci siê w granicach sprite'a
	return bounds.contains(static_cast<sf::Vector2f>(mousePos));
}

void Maps::draw(sf::RenderWindow& window) {
	mapsBackground->render(window);
	window.draw(backSprite);
	// Rysowanie sprite'ów
	for (size_t i = 0; i < mapsItems.size(); i++) {
		window.draw(mapsItems[i]);
	}
}

