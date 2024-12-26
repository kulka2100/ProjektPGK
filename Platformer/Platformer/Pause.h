#pragma once
#include "stdafx.h"
#include "Background.h"
#include "TextureManager.h"
#include "Button.h"

class Pause : public Button
{
private:
	sf::Font font;
	Background* background;
	sf::Texture playTexture;
	sf::Texture stopTexture;
	sf::Sprite backSprite;
	sf::Texture backTexture;
	std::vector<sf::Sprite> pauseItems;

	void initItems();

public:
	Pause(float width, float height);
	~Pause() {
		delete background;
	}

	void draw(sf::RenderWindow& window);

	std::vector<sf::Sprite>& getPauseItems();

};

