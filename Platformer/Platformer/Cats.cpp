#include "stdafx.h"
#include "Cats.h"

Cats::Cats(sf::Vector2f startPosition, float speed, float leftBoundary, float rightBoundary)
    : Enemy(startPosition, speed, leftBoundary, rightBoundary) {
    this->initTexture();
    this->health = 6;
    this->textureRightAttack1.loadFromFile("textury/cat9.png");
    this->textureRightAttack2.loadFromFile("textury/cat10.png");
    this->textureLeftAttack1.loadFromFile("textury/cat7.png");
    this->textureLeftAttack2.loadFromFile("textury/cat8.png");
    sprite.setTextureRect(sf::IntRect(0, 0, textureRightAttack1.getSize().x, textureRightAttack1.getSize().y));

}



Cats::~Cats() {}


void Cats::initTexture() {
    std::unique_ptr<sf::Texture> tempTexture;

    // Ładowanie tekstur
    for (int i = 5; i <= 6; i++) {
        tempTexture = std::make_unique<sf::Texture>();
        if (!tempTexture->loadFromFile("textury/cat" + std::to_string(i) + ".png")) {
            std::cerr << "Nie udało się załadować tekstury: cat" + std::to_string(i) + ".png" << std::endl;
        }
        else {
            this->rightTextures.push_back(std::move(*tempTexture));
        }
    }

    for (int i = 2; i <= 3; i++) {
        tempTexture = std::make_unique<sf::Texture>();
        if (!tempTexture->loadFromFile("textury/cat" + std::to_string(i) + ".png")) {
            std::cerr << "Nie udało się załadować tekstury: cat" + std::to_string(i) + ".png" << std::endl;
        }
        else {
            this->leftTextures.push_back(std::move(*tempTexture));
        }
    }

    float scaleFactor = 1.0f;
    this->sprite.setScale(scaleFactor, scaleFactor);
}