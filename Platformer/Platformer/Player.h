#pragma once
#include "Bullet.h"
#include "TextureManager.h"
class Player
{
private:
	int health;
	int keys = 0;
	sf::Sprite playerSprite;
	sf::Sprite playerDeadSprite;
	std::vector<sf::Texture> rightTextures;
	std::vector<sf::Texture> leftTextures;
	std::vector<sf::Texture> hpTextures;
	std::vector<sf::Sprite> hpSprite;

	int currentAmmo = 15;
	sf::Text ammoText;
	sf::Font font;
	sf::Texture amuTexture;
	sf::Sprite amuSprite;

	TextureManager textureManager;

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
	bool canMoveRight = true;
	bool canMoveLeft = true;
	bool isDead = false;
	bool isFalling = false;
	bool isDeadSpriteSet = false;

	void initText();
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

	//Umozliwienie ruchu w prawo
	void setCanMoveRight(bool canMove) {
		this->canMoveRight = canMove;
	}

	//Umozliwienie ruchu w lewo
	void setCanMoveLeft(bool canMove) {
		this->canMoveLeft = canMove;
	}

	void setIsDead(bool isDead) {
		this->isDead = isDead;
	}

	void incrementCurrentAmo();

	void updateAmmoText(int currentAmmo);

	int getCurrentAmo();

	void updateHealth();

	int getCurrentHealth() const;

	bool getIsDead() {
		return isDead;
	}

	void setKeys(int keys) {
		this->keys = keys;
	}

	int getKeys() {
		return keys;
	}
};

	