#include "stdafx.h"
#include "Obstacle.h"


Obstacle::Obstacle(sf::Texture& obstacleTexture, sf::Vector2f position, ObstacleType type) : obstacleType(type) {
	this->obstacleTexture = &obstacleTexture;
	if (this->obstacleTexture) { // Sprawdzenie, czy wskaŸnik nie jest pusty
		this->itemSprite.setTexture(obstacleTexture);
	}
	this->damageInterval = 0.5f;
	this->itemSprite.setPosition(position);
}



