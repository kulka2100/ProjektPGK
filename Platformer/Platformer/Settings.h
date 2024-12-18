#pragma once
#include "Menu.h"
#include "Button.h"
#include "TextureManager.h"

class Settings : public Button, Menu
{
private:
	std::vector <sf::Sprite> settingsItems;
	std::vector <sf::Texture> settingsTextures;
	TextureManager textureManager;

public:
	Settings(float width, float height);

	std::vector <sf::Sprite>& getItems();

	void draw(sf::RenderWindow& window);
};

