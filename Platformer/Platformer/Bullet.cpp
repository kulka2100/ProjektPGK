#include "stdafx.h"
#include "Bullet.h"


Bullet::Bullet(sf::Texture& texture, sf::Vector2f startPos, sf::Vector2f direction, float bulletSpeed) {
	this->startPos = startPos;
	this->direction = direction;
	this->bulletSpeed = bulletSpeed;
	this->velocity = direction * bulletSpeed;
	this->bulletSprite.setTexture(texture);
	this->bulletSprite.setPosition(startPos.x + 35, startPos.y + 50);
}

Bullet::~Bullet()
{
}

bool Bullet::isOffScreen() {
	// Za³ó¿my, ¿e ekran koñczy siê na szerokoœci 800 i wysokoœci 600
	sf::Vector2f position = bulletSprite.getPosition();
	return position.x < 0 || position.x > 800 || position.y < 0 || position.y > 600;
}


void Bullet::update(float deltaTime) {
	sf::Vector2f position = bulletSprite.getPosition();
	bulletSprite.move(velocity * deltaTime);
}


void Bullet::render(sf::RenderTarget* target) const{
	if (target)
		target->draw(bulletSprite);
}

sf::FloatRect Bullet::getBounds() const {
	return this->bulletSprite.getGlobalBounds();
}

