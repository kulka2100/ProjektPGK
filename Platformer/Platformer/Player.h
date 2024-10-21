#pragma once
class Player
{
private:
	sf::Sprite sprite;
	std::vector<sf::Texture> rightTextures;
	std::vector<sf::Texture> leftTextures;
	std::vector<sf::Texture> upTextures;
	std::vector<sf::Texture> downTextures;
	sf::Texture upTexture;
	
	float animationTimer;                // Zegar animacji
	float animationTimerMax;             // Maksymalny czas trwania jednej klatki
	unsigned int animationIndex;

	// Pozycja postaci na ekranie
	float characterX = 400.0f;
	float characterY = 300.0f;
	float characterSpeed; // Szybkoœæ poruszania postaci

	void initSprite();
	void initTexture();

public:
	Player(float speed);

	~Player();

	void render(sf::RenderTarget& target);

	void update(float deltaTime);
};

