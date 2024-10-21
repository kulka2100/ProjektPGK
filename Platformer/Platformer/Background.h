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


	void adjustBackground(sf::RenderWindow& window);

};

