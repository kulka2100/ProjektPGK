#pragma once
#include "Bullet.h"
class Player
{
private:
	sf::Sprite playerSprite;
	std::vector<sf::Texture> rightTextures;
	std::vector<sf::Texture> leftTextures;
	std::vector<sf::Texture> upTextures;
	std::vector<sf::Texture> downTextures;
	sf::Texture upTexture;

	std::vector<Bullet> bullets;
	sf::Texture bulletTexture;
	float bulletDir;


	// Zegar animacji
	float animationTimer;               
	// Maksymalny czas trwania jednej klatki
	float animationTimerMax;            
	unsigned int animationIndex;

	// Poczatkowa pozycja postaci na ekranie
	sf::Vector2f playerPosition;
	// Szybkoœæ poruszania postaci
	float characterSpeed; 
	//Grawitacja
	const float GRAVITY = 5.7f;
	const float JUMP_STRENGTH = -0.75f;
	float verticalVelocity = 0.0f;
	bool isJumping = false;


	void initSprite();
	void initTexture();

public:
	Player(sf::Vector2f playerPosition,float speed);

	~Player();




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

	void shoot();



	void update(float deltaTime,sf::Event &event);

	void render(sf::RenderTarget& target);
};

