#pragma once
#include "TextureManager.h"
class Button
{
protected:
	sf::Sprite backSprite;
public:
	//Metoda zwracajaca index kliknietego elementu
	int getHoverIndex(sf::RenderWindow& window, std::vector<sf::Sprite>& items);

	//Zmiana koloru po najechaniu na dany sprite
	void handleHover(sf::RenderWindow& window, std::vector<sf::Sprite>& items);
	//Sprawdzenie czy akutalna pozycja myszy pokrwa sie ze sprite
	bool isMouseHover(const sf::Sprite& sprite, const sf::RenderWindow& window);
};

