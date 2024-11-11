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
	
};

