#pragma once
#include "stdafx.h"
#include "Item.h"

enum class ObstacleType {
	Platform,
	Stone,
	Spikes,
	Scythe,
	Lava,
	FallingStone
};

class Obstacle : public Item
{
private:
	sf::Texture *obstacleTexture;
	ObstacleType obstacleType;
	sf::Vector2f initialPosition; // Pocz¹tkowa pozycja przeszkody


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


	// Resetowanie pozycji na pocz¹tkow¹
	void resetPosition() {
		this->itemSprite.setPosition(initialPosition);
	}

	// Ustawienie nowej pozycji pocz¹tkowej
	void setInitialPosition(const sf::Vector2f& position) {
		initialPosition = position;
	}

	// Uzyskanie pozycji pocz¹tkowej
	sf::Vector2f getInitialPosition() const {
		return initialPosition;
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

