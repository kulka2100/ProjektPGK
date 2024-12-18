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


Maps::Maps(const std::string & filename, int width) {
	background = new Background(filename);
	initMaps(width);
}

std::vector <sf::Sprite>& Maps::getItems() {
	return mapsItems;
}


void Maps::draw(sf::RenderWindow& window) {
	background->render(window);
	window.draw(backSprite);
	// Rysowanie sprite'ów
	for (size_t i = 0; i < mapsItems.size(); i++) {
		window.draw(mapsItems[i]);
	}
}

