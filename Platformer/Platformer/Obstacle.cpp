#include "stdafx.h"
#include "Obstacle.h"


Obstacle::Obstacle(sf::Texture& obstacleTexture, sf::Vector2f position, ObstacleType type)
    : obstacleTexture(&obstacleTexture), obstacleType(type), initialPosition(position), damageInterval(0.5f) {
	if (this->obstacleTexture) { // Sprawdzenie, czy wskaŸnik nie jest pusty
		this->itemSprite.setTexture(obstacleTexture);
	}
    this->itemSprite.setPosition(position); // Ustawienie pozycji sprite'a
}


bool Obstacle::canDealDamage() {
	// Sprawdzanie, czy min?? czas od ostatniego zadania obra?e?
	if (damageClock.getElapsedTime().asSeconds() >= damageInterval) {
		damageClock.restart();
		return true;
	}
	return false;
}
