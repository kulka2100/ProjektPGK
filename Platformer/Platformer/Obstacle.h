#pragma once
#include "stdafx.h"
#include "Item.h"

class Obstacle : public Item
{
private:
	sf::Texture *obstacleTexture;

public:
	Obstacle(sf::Texture& obstacleTexture, sf::Vector2f position);

	// Metoda do uzyskania referencji do tekstury
	sf::Texture& getTexture() override {
		return *obstacleTexture;
	}
};

