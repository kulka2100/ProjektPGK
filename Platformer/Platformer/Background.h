#pragma once
#include "Player.h"
class Background
{
private:
	sf::Texture textureBackground;
	sf::Sprite backgroundSprite;
	float speed;
	sf::Vector2f position;
	Player* player;


public:
	Background(const std::string& filname, Player *player);
	Background(const std::string& filname);
	bool isUpdated = false;
	bool moveLeft = false;
	bool moveRight = false;

	void update(float deltaTime, float characterSpeed);

	void render(sf::RenderTarget& target);

	// Metoda do ustawienia prêdkoœci t³a
	void setSpeed(float newSpeed) {
		speed = newSpeed;
	}


	sf::Sprite& getBackgroundSprite();

	sf::Texture& getBackgroundTexture();


};

