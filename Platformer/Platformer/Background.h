#pragma once
class Background
{
private:
	sf::Texture textureBackground;
	sf::Sprite sprite;
	float speed;
	sf::Vector2f position;

public:
	Background(const std::string& filname);

	void update(float deltaTime);

	void render(sf::RenderTarget& target);

	// Metoda do ustawienia prêdkoœci t³a
	void setSpeed(float newSpeed) {
		speed = newSpeed;
	}


	void followPlayer( sf::Vector2f& playerPosition, sf::RenderWindow& window);


};

