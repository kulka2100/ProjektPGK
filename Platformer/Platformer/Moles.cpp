#include "stdafx.h"
#include "Moles.h"


Moles::Moles(sf::Vector2f startPosition, float speed, float leftBoundary, float rightBoundary)
    : Enemy(startPosition, speed, leftBoundary, rightBoundary) {
    this->health = 3;
    this->initTexture();
    this->textureRightAttack1.loadFromFile("textury/mole9.png");
    this->textureRightAttack2.loadFromFile("textury/mole10.png");
    this->textureLeftAttack1.loadFromFile("textury/mole7.png");
    this->textureLeftAttack2.loadFromFile("textury/mole8.png");
}



Moles::~Moles() {}

void Moles::initTexture() {
    std::unique_ptr<sf::Texture> tempTexture;

    // Ładowanie tekstur
    for (int i = 5; i <= 6; i++) {
        tempTexture = std::make_unique<sf::Texture>();
        if (!tempTexture->loadFromFile("textury/mole" + std::to_string(i) + ".png")) {
            std::cerr << "Nie udało się załadować tekstury: mole" + std::to_string(i) + ".png" << std::endl;
        }
        else {
            this->rightTextures.push_back(std::move(*tempTexture));
        }
    }

    for (int i = 2; i <= 3; i++) {
        tempTexture = std::make_unique<sf::Texture>();
        if (!tempTexture->loadFromFile("textury/mole" + std::to_string(i) + ".png")) {
            std::cerr << "Nie udało się załadować tekstury: mole" + std::to_string(i) + ".png" << std::endl;
        }
        else {
            this->leftTextures.push_back(std::move(*tempTexture));
        }
    }

    float scaleFactor = 0.17f;
    this->sprite.setScale(scaleFactor, scaleFactor);
}
