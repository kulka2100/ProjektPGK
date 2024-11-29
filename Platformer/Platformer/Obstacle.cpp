#include "stdafx.h"
#include "Obstacle.h"


Obstacle::Obstacle(sf::Texture& obstacleTexture, sf::Vector2f position) {
	this->obstacleTexture = &obstacleTexture;
	if (this->obstacleTexture) { // Sprawdzenie, czy wskaŸnik nie jest pusty
		this->obstacleSprite.setTexture(obstacleTexture);
	}
	this->obstacleSprite.setPosition(position);

}


sf::FloatRect Obstacle::getObstacleBounds() {
	return obstacleSprite.getGlobalBounds();
}


sf::Vector2f Obstacle::getObstaclePosition() {
	return obstacleSprite.getPosition();
}


void Obstacle::update(sf::Vector2f pos) {
	obstacleSprite.move(pos);
}

void Obstacle::render(sf::RenderWindow& window) const {
	window.draw(obstacleSprite);
}
