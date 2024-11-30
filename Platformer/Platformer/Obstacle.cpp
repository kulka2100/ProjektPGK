#include "stdafx.h"
#include "Obstacle.h"


Obstacle::Obstacle(sf::Texture& obstacleTexture, sf::Vector2f position) {
	this->obstacleTexture = &obstacleTexture;
	if (this->obstacleTexture) { // Sprawdzenie, czy wskaŸnik nie jest pusty
		this->itemSprite.setTexture(obstacleTexture);
	}
	this->itemSprite.setPosition(position);

}



