#pragma once
#include "stdafx.h"
#include "Item.h"

enum class ObstacleType {
	Platform,
	Stone,
	Spikes,
	Scythe,
	Lava,
};

class Obstacle : public Item
{
private:
	sf::Texture *obstacleTexture;
	ObstacleType obstacleType;

	sf::Clock damageClock;
	float damageInterval;

public:
	Obstacle(sf::Texture& obstacleTexture, sf::Vector2f position, ObstacleType type);

	// Metoda do uzyskania referencji do tekstury
	sf::Texture& getTexture() override {
		return *obstacleTexture;
	}


	ObstacleType getType() const {
		return obstacleType;
	}


	bool canDealDamage() {
		// Sprawdzanie, czy min?? czas od ostatniego zadania obra?e?
		if (damageClock.getElapsedTime().asSeconds() >= damageInterval) {
			damageClock.restart();
			return true;
		}
		return false;
	}
};

