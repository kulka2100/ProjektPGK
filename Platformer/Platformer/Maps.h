#pragma once
#include "stdafx.h"
#include "Background.h"
#include "Button.h"
#include "Menu.h"
#include "TextureManager.h"
class Maps : public Button, Menu
{
private:
	std::vector <sf::Sprite> mapsItems;
	std::vector <sf::Texture> mapsTextures;
	TextureManager textureManager;

public:

	Maps(const std::string& filename, int width);

	~Maps() {}

	//Inicjalizacja miniaturek map
	void initMaps(int width);

	std::vector <sf::Sprite>& getItems();

	void draw(sf::RenderWindow& window);

};

