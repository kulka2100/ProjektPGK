#include "stdafx.h"
#include "Enemy.h"

void Enemy::initTexture() {
    std::unique_ptr<sf::Texture> tempTexture;
    for (int i = 5; i <= 6; i++) {
        tempTexture = std::make_unique<sf::Texture>();
        if (!tempTexture->loadFromFile("textury/mole" + std::to_string(i) + ".png")) {
            std::cerr << "Nie uda³o siê za³adowaæ tekstury: mole" + std::to_string(i) + ".png" << std::endl;
        }
        else {
            this->rightTextures.push_back(std::move(*tempTexture));
        }
    }

    for (int i = 2; i <= 3; i++) {
        tempTexture = std::make_unique<sf::Texture>();
        if (!tempTexture->loadFromFile("textury/mole" + std::to_string(i) + ".png")) {
            std::cerr << "Nie uda³o siê za³adowaæ tekstury: mole" + std::to_string(i) + ".png" << std::endl;
        }
        else {
            this->leftTextures.push_back(std::move(*tempTexture));
        }
    }

    // Skalowanie sprite'a
    float scaleFactor = 0.17f;
    this->sprite.setScale(scaleFactor, scaleFactor);
}

Enemy::Enemy(sf::Vector2f startPosition, float speed, float leftBoundary, float rightBoundary)
    : position(startPosition), speed(speed), leftBoundary(leftBoundary), rightBoundary(rightBoundary), direction(1.0f) {
    this->animationTimer = 0.0f;
    this->animationTimerMax = 0.2f; 
    this->animationIndex = 0;
    this->initTexture();
    this->position.y = GROUND_Y - this->sprite.getGlobalBounds().height;
    this->initSprite();
}

Enemy::~Enemy() {}

void Enemy::update(float deltaTime) {
    this->animationTimer += deltaTime;
    if (this->animationTimer >= this->animationTimerMax) {
        this->animationIndex++;
        this->animationTimer = 0.0f;

        if (direction > 0) { // Ruch w prawo
            if (this->animationIndex >= this->rightTextures.size()) {
                this->animationIndex = 0;
            }
            this->sprite.setTexture(this->rightTextures[this->animationIndex]);
        }
        else { // Ruch w lewo
            if (this->animationIndex >= this->leftTextures.size()) {
                this->animationIndex = 0;
            }
            this->sprite.setTexture(this->leftTextures[this->animationIndex]);
        }
    }
    // Przeciwnik porusza siê w ustalonym kierunku
    this->position.x += this->speed * this->direction * deltaTime;

    // Zmiana kierunku przy dotarciu do granicy
    if (this->position.x <= this->leftBoundary) {
        this->direction = 1.0f;
    }
    else if (this->position.x >= this->rightBoundary) {
        this->direction = -1.0f;
    }
    this->position.y = GROUND_Y - this->sprite.getGlobalBounds().height;
    this->sprite.setPosition(this->position);

}

void Enemy::render(sf::RenderWindow& window) {
    window.draw(this->sprite);
}

sf::FloatRect Enemy::getBounds() const {
    return this->sprite.getGlobalBounds();
}

void Enemy::initSprite() {
    if (!rightTextures.empty()) {
        this->sprite.setTexture(rightTextures[0]); // Ustawienie domyœlnej tekstury
    }
    else {
        std::cerr << "Brak tekstur w wektorze rightTextures podczas inicjalizacji sprite'a!" << std::endl;
    }
    this->sprite.setPosition(this->position);
}

