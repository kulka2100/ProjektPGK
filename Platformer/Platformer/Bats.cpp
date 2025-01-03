#include "stdafx.h"
#include "Bats.h"

Bats::Bats(sf::Vector2f startPosition, float speed, float leftBoundary, float rightBoundary)
    : Enemy(startPosition, speed, leftBoundary, rightBoundary) {
    this->initTexture();
    this->health = 2;
    this->textureRightAttack1.loadFromFile("textury/bat5.png");
    this->textureRightAttack2.loadFromFile("textury/bat6.png");
    this->textureLeftAttack1.loadFromFile("textury/bat5.png");
    this->textureLeftAttack2.loadFromFile("textury/bat6.png");
    sprite.setTextureRect(sf::IntRect(0, 0, textureRightAttack1.getSize().x, textureRightAttack1.getSize().y));
    this->rotationAngle = 0.0f;
    this->rotationBatSpeed = 100.0f;

}



Bats::~Bats() {}


void Bats::initTexture() {
    std::unique_ptr<sf::Texture> tempTexture;

    // Ładowanie tekstur
    for (int i = 1; i <= 4; i++) {
        tempTexture = std::make_unique<sf::Texture>();
        if (!tempTexture->loadFromFile("textury/bat" + std::to_string(i) + ".png")) {
            std::cerr << "Nie udało się załadować tekstury: bat" + std::to_string(i) + ".png" << std::endl;
        }
        else {
            this->rightTextures.push_back(std::move(*tempTexture));
        }
    }

    float scaleFactor = 1.0f;
    this->sprite.setScale(scaleFactor, scaleFactor);
}

void Bats::update(float deltaTime) {
    if (this->isDying) {
        this->updateDeathAnimation(deltaTime);
        return; // Nie wykonuj standardowych operacji ruchu
    }
    if (isAttacking) {
        this->updateAttack();
        return;
    }

    this->animationTimer += deltaTime;
    if (this->animationTimer >= this->animationTimerMax) {
        this->animationIndex++;
        this->animationTimer = 0.0f;

        if (this->animationIndex >= this->rightTextures.size()) {
            this->animationIndex = 0;
        }
        this->sprite.setTexture(this->rightTextures[this->animationIndex]);
    }

    // Zaktualizowana logika poruszania się w kółko
    this->rotationAngle += rotationBatSpeed * deltaTime;  // Zwiększanie kąta rotacji

    if (this->rotationAngle >= 360.0f) {
        this->rotationAngle -= 360.0f;  
    }

    // Ustalanie nowej pozycji na okręgu
    float radius = 0.7f;  // Promień okręgu, w którym porusza się postać
    float centerX = this->position.x;  // Środek okręgu w osi X
    float centerY = this->position.y;  // Środek okręgu w osi Y

    // Obliczanie nowych współrzędnych na okręgu
    this->position.x = centerX + radius * std::cos(this->rotationAngle * (3.14159f / 180.0f));
    this->position.y = centerY + radius * std::sin(this->rotationAngle * (3.14159f / 180.0f));


    // Zaktualizowanie pozycji sprite'a
    this->sprite.setPosition(this->position);
}
