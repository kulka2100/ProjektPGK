#pragma once
class Player
{
private:
	sf::Sprite playerSprite;
	std::vector<sf::Texture> rightTextures;
	std::vector<sf::Texture> leftTextures;
	std::vector<sf::Texture> upTextures;
	std::vector<sf::Texture> downTextures;
	sf::Texture upTexture;


	// Zegar animacji
	float animationTimer;               
	// Maksymalny czas trwania jednej klatki
	float animationTimerMax;            
	unsigned int animationIndex;

	// Poczatkowa pozycja postaci na ekranie
	sf::Vector2f playerPosition;
	// Szybkoœæ poruszania postaci
	float characterSpeed; 

	void initSprite();
	void initTexture();

public:
	Player(sf::Vector2f playerPosition,float speed);

	~Player();

	void render(sf::RenderTarget& target);

	void update(float deltaTime);

	//Metoda zwracajaca biezaca pozycje postaci
	sf::Vector2f getPlayerPosition() {
		return this->playerSprite.getPosition();
	}

	sf::Sprite getPlayerSprite() {
		return playerSprite;
	}

	float getCharacterSpeed() {
		return characterSpeed;
	}
};

