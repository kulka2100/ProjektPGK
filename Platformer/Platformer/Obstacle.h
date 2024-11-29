#pragma once
#include "stdafx.h"

class Obstacle
{
private:
	sf::Texture *obstacleTexture;
	sf::Sprite obstacleSprite;

public:
	Obstacle(sf::Texture& obstacleTexture, sf::Vector2f position);

	sf::FloatRect getObstacleBounds();

	sf::Vector2f getObstaclePosition();

	void update(sf::Vector2f pos);

	void render(sf::RenderWindow& window) const;

	// Metoda do uzyskania referencji do sprite'a (w celu kolizji pikselowej)
	sf::Sprite& getSprite() {
		return obstacleSprite;
	}

	// Metoda do uzyskania referencji do tekstury (w celu kolizji pikselowej)
	sf::Texture& getTexture() {
		return *obstacleTexture;
	}


	
};

