#pragma once
#include "stdafx.h"
#include "Background.h"
#include "TextureManager.h"
class Maps
{
private:
	std::vector <sf::Sprite> mapsItems;
	std::vector <sf::Texture> mapsTextures;
	Background* mapsBackground;
	TextureManager textureManager;

public:

	Maps(const std::string& filename, int width) {
		mapsBackground = new Background(filename);
		initMaps(width);
	}

	~Maps() {
		delete mapsBackground;
	}

	//Inicjalizacja miniaturek map
	void initMaps(int width);

	//Metoda zwracajaca index kliknietego elementu
	int getMapIndex(sf::RenderWindow& window);

	//Zmiana koloru po najechaniu na dany sprite
	void handleHover(sf::RenderWindow& window);

	//Sprawdzenie czy akutalna pozycja myszy pokrwa sie ze sprite
	bool isMouseHover(const sf::Sprite& sprite, const sf::RenderWindow& window);

	void draw(sf::RenderWindow& window);

};

