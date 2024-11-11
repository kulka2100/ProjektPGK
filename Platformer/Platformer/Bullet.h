#pragma once
class Bullet
{
private:
	sf::Sprite bulletSprite;
	sf::Vector2f startPos;
	sf::Vector2f direction;
	sf::Vector2f velocity;  // Pr�dko�� pocisku
	float bulletSpeed;

public:
	Bullet(sf::Texture& texture, sf::Vector2f startPos, sf::Vector2f direction, float bulletSpeed);

	~Bullet();

	// Sprawdzanie, czy pocisk znajduje si� poza ekranem (dla usuni�cia go z listy)
	bool isOffScreen();

	sf::Vector2f getBulletPosition() {
		return bulletSprite.getPosition();
	}

	sf::Sprite& getBulletSprite() {
		return bulletSprite;
	}


	void update(float deltaTime);


	void render(sf::RenderTarget* target) const;
};


