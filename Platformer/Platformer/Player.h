#pragma once
#include "Bullet.h"
class Player
{
private:
	int health;
	sf::Sprite playerSprite;
	std::vector<sf::Texture> rightTextures;
	std::vector<sf::Texture> leftTextures;

	//Grawitacja
	const float GRAVITY = 980.f;
	const float JUMP_STRENGTH = -550.f;
	float verticalVelocity = 0.0f;

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
	//Zmienne stanu
	bool isJumping = false;
	bool isOnGround = false;


	void initSprite();
	void initTexture();

	//Strzaly
	float shootCooldown;
	float shootCooldownMax;

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

	sf::FloatRect getPlayerBounds() {
		return playerSprite.getGlobalBounds();
	}

	int getHealth() const;
	void reduceHealth(int amount);

	void updateAnimations(float deltaTime);

	void shoot();

	// Dodawanie grawitacji, aby postaæ wraca³a na ziemiê
	void gravitation(float deltaTime);

	//Zatrzymanie postaci gdy dojdzie do krawedzi
	void holdPlayerAtEdges();

	void setOnGround(bool isOnGround);

	void setVerticalVelocity(float verticalVelocity);

	//Aktualizacja ruchu postaci
	void update(float deltaTime,sf::Event &event);

	void render(sf::RenderTarget& target);

	bool getIsJumping() const;
	void setIsJumping(bool jumping);
	float getVerticalVelocity() const;
	std::vector<Bullet>& getBullets();

};

	