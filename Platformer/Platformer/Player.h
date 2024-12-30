#pragma once
#include "Bullet.h"
#include "TextureManager.h"
#include "GameState.h"
#include "CollectableItem.h"

struct EquippedItem {
	ItemType type;
	sf::Sprite sprite;
};

class Player
{
private:
	int health;
	float damageCooldown; // Czas do następnego możliwego otrzymania obrażeń
	int keys = 0;
	sf::Sprite playerSprite;
	sf::Sprite playerDeadSprite;
	std::vector<sf::Texture> rightTextures;
	std::vector<sf::Texture> leftTextures;
	std::vector<sf::Texture> hpTextures;
	std::vector<sf::Sprite> hpSprite;
	std::vector<EquippedItem> equippedItems;
	


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

	GameState gameState;
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
	// Szybkość poruszania postaci
	float characterSpeed; 
	//Zmienne stanu
	bool isJumping = false;
	bool isOnGround = false;
	bool canMoveRight = true;
	bool canMoveLeft = true;
	bool isDead = false;
	bool isFalling = false;
	bool fallen = false;
	bool isDeadSpriteSet = false;
	bool movingWithEqRight = false;
	bool movingWithEqLeft = false;


	void initText();
	void initSprite();
	void initTexture();


	//Strzaly
	float shootCooldown;
	float shootCooldownMax;
	int experience;       
	int level;            
	int experienceToNext; 
	int maxHealth;        
	int damage;                  



public:
	Player(sf::Vector2f playerPosition, int hp);

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

	// Dodawanie grawitacji, aby postać wracała na ziemię
	void gravitation(float deltaTime);

	//Zatrzymanie postaci gdy dojdzie do krawedzi
	void holdPlayerAtEdges();

	void setOnGround(bool isOnGround);

	void setVerticalVelocity(float verticalVelocity);

	//Aktualizacja ruchu postaci
	void update(float deltaTime,sf::Event &event);

	void render(sf::RenderTarget& target);

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

	void setPlayerPosition(float posx, float posy) {
		this->playerSprite.setPosition(posx, posy);
	}

	void setIsDead(bool isDead) {
		this->isDead = isDead;
	}

	void setFallen(bool fallen) {
		this->fallen = fallen;
	}

	void setKeys(int keys) {
		this->keys = keys;
	}

	void setCurrentAmo(int amo) {
		this->currentAmmo = amo;
	}

	void setHealth(int health) {
		hpSprite.clear();
		this->health = health;
	}

	void updateHealthVector() {
		hpSprite.clear(); // Wyczyść aktualny stan wektora

		if (!hpTextures.empty()) {
			for (int i = 0; i < health; ++i) {
				sf::Sprite newSprite;
				newSprite.setTexture(hpTextures[0]);

				sf::Vector2f position;
				if (i == 0) {
					position = sf::Vector2f(10.f, 25.f); // Pierwszy sprite
				}
				else {
					position = sf::Vector2f(hpSprite.back().getPosition().x + 45, 25.f);
				}
				newSprite.setPosition(position);
				hpSprite.push_back(newSprite);
			}
		}
		else {
			std::cerr << "hpTextures jest pusty! Nie można dodać sprite'a." << std::endl;
		}
	}


	void incrementCurrentAmo();

	void updateAmmoText(int currentAmmo);

	void updateHealth(int count = 1);

	bool getIsJumping() const;

	int getCurrentAmo();

	int getCurrentHealth() const;

	bool getIsDead() {
		return isDead;
	}

	int getKeys() {
		return keys;
	}

	bool getIsFallen() {
		return fallen;
	}

	bool canTakeDamage() const {
		return damageCooldown <= 0;
	}

		
	void setEqTexture(const std::string& filepath, const std::string& name, ItemType itemType) {
		textureManager.loadTexture(filepath, name);
		sf::Texture* texture = textureManager.getTexture(name);
		if (texture) {
				sf::Sprite sprite;
				sprite.setTexture(*texture);

				// Ustawianie pozycji w zależności od typu przedmiotu
				switch (itemType) {
				case ItemType::Hat:
					sprite.setPosition(getPlayerPosition().x, getPlayerPosition().y - 25);
					break;
				case ItemType::Wings:
					sprite.setPosition(getPlayerPosition().x - 100, getPlayerPosition().y);
					break;
				case ItemType::Saw:
					sprite.setPosition(getPlayerPosition().x+ 80, getPlayerPosition().y);
					break;
				}
				equippedItems.push_back({ itemType, sprite });
			}
		else {
			std::cout << "Nie udalo sie załadowac tekstury: " << name << "\n";
			}	
	}

	void updateEqPosition() {
		for (auto& eqItem : equippedItems) {
			switch (eqItem.type) {
			case ItemType::Hat:
				eqItem.sprite.setPosition(getPlayerPosition().x+ 10, getPlayerPosition().y - 28);
				if (movingWithEqLeft) {
					eqItem.sprite.setPosition(getPlayerPosition().x + 70, getPlayerPosition().y - 28);
				}
				break;
			case ItemType::Wings:
				eqItem.sprite.setPosition(getPlayerPosition().x - 33, getPlayerPosition().y);
				if (movingWithEqLeft) {
					eqItem.sprite.setPosition(getPlayerPosition().x + 118, getPlayerPosition().y);
				}
				break;
			case ItemType::Saw:
				eqItem.sprite.setPosition(getPlayerPosition().x + 35, getPlayerPosition().y + 17);
				if (movingWithEqLeft) {
					eqItem.sprite.setPosition(getPlayerPosition().x + 38, getPlayerPosition().y + 17);
				}
				break;
			default:
				break;
			}


			if (movingWithEqRight) {
				eqItem.sprite.setScale(1.0, 1.0);
			}
			else if (movingWithEqLeft) {
				eqItem.sprite.setScale(-1.0, 1.0);
			}
		}
	}

	void addExperience(int amount);
	void levelUp();
	int getLevel() const;
	int getExperience() const;
	int getExperienceToNext() const;
	int getMaxHealth() const;
	int getDamage() const;
};

	