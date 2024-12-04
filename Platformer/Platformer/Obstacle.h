#pragma once
#include "stdafx.h"
#include "Item.h"

enum class ObstacleType {
	Platform,
	Stone,
};

class Obstacle : public Item
{
private:
	sf::Texture *obstacleTexture;
	ObstacleType obstacleType;

public:
	Obstacle(sf::Texture& obstacleTexture, sf::Vector2f position, ObstacleType type);

	// Metoda do uzyskania referencji do tekstury
	sf::Texture& getTexture() override {
		return *obstacleTexture;
	}


	ObstacleType getType() const {
		return obstacleType;
	}
};

