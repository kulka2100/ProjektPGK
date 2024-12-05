#include "stdafx.h"
#include "Boss.h"

Boss::Boss(sf::Vector2f startPosition, float speed, float leftBoundary, float rightBoundary)
    : Enemy(startPosition, speed, leftBoundary, rightBoundary) {
    this->initTexture();
    this->health = 15;
    this->textureLeftAttack1.loadFromFile("textury/boss6.png");
    this->textureLeftAttack2.loadFromFile("textury/boss7.png");
    sprite.setTextureRect(sf::IntRect(0, 0, textureLeftAttack1.getSize().x, textureLeftAttack1.getSize().y));
    this->jumpTimer = 0;
    this->isJumping = false;
    this->jumpDuration = 0.8f;
    this->bulletTexture.loadFromFile("textury/boss_bullet.png");
}



Boss::~Boss() {}


void Boss::initTexture() {
    std::unique_ptr<sf::Texture> tempTexture;

    for (int i = 2; i <= 5; i++) {
        tempTexture = std::make_unique<sf::Texture>();
        if (!tempTexture->loadFromFile("textury/boss" + std::to_string(i) + ".png")) {
            std::cerr << "Nie udało się załadować tekstury: boss" + std::to_string(i) + ".png" << std::endl;
        }
        else {
            this->leftTextures.push_back(std::move(*tempTexture));
        }
    }

    float scaleFactor = 2.5f;
    this->sprite.setScale(scaleFactor, scaleFactor);
}

void Boss::update(float deltaTime) {
    if (this->isDying) {
        this->updateDeathAnimation(deltaTime);
        return; // Nie wykonuj standardowych operacji ruchu
    }
    if (isAttacking) {
        this->updateAttack();
        return;
    }

    // Obs³uga animacji 
    this->animationTimer += deltaTime;
    if (this->animationTimer >= this->animationTimerMax) {
        this->animationIndex++;
        this->animationTimer = 0.0f;
        if (this->animationIndex >= this->leftTextures.size()) {
            this->animationIndex = 0;
        }

        this->sprite.setTexture(this->leftTextures[this->animationIndex]);
    }

    // Obsługa skoku
    this->jumpTimer += deltaTime;
    if (this->jumpTimer >= 2.0f) { // Skok co 2 sekundy
        this->jumpTimer = 0.0f;
        this->isJumping = true;
        this->jumpTime = 0.0f;
        this->sprite.setTexture(this->leftTextures[2]); // Użyj tekstury skoku
    }

    if (this->isJumping) {
        this->jumpTime += deltaTime;

        // Przykładowa parabola skoku (y = -4x^2 + 4x, gdzie x \in [0, 1])
        float jumpHeight = 200.0f; // Maksymalna wysokość skoku
        float jumpProgress = this->jumpTime / this->jumpDuration;

        if (jumpProgress >= 1.0f) {
            this->isJumping = false; // Koniec skoku
        }
        else {
            float jumpOffset = -4.0f * jumpProgress * jumpProgress + 4.0f * jumpProgress;
            this->sprite.setPosition(this->position.x, this->position.y - jumpOffset * jumpHeight);
        }
    }
    else {
        // Zaktualizuj pozycję sprite'a (bez wymuszania pozycji Y)
        this->sprite.setPosition(this->position);
    }
    // Obsługa strzelania w lewą stronę
    this->shootTimer += deltaTime; // Timer odliczający czas do kolejnego strzału
    if (this->shootTimer >= this->shootInterval) { // Strzał co określony czas
        this->shootTimer = 0.0f;

        // Losowanie wysokości strzału
        static std::random_device rd;  
        static std::mt19937 gen(rd()); 
        std::uniform_real_distribution<float> distY(0.0f, this->sprite.getGlobalBounds().height);

        float randomYOffset = distY(gen); // Losowa wartość przesunięcia na osi Y

        // Dodanie nowego pocisku do listy
        sf::Vector2f bulletDirection(-1.0f, 0.0f); // Kierunek: w lewo
        sf::Vector2f bulletStartPos = this->sprite.getPosition();
        bulletStartPos.y += randomYOffset; // Ustawienie losowej wysokości
        bullets.emplace_back(this->bulletTexture, bulletStartPos, bulletDirection, this->bulletSpeed);
    }

    // Aktualizacja istniejących pocisków
    for (auto it = bullets.begin(); it != bullets.end(); ) {
        it->update(deltaTime);
        if (it->isOffScreen()) {
            it = bullets.erase(it); // Usuwanie pocisku, który wyszedł poza ekran
        }
        else {
            ++it;
        }
    }
}

void Boss::render(sf::RenderWindow& window) {
    if (isAttacking) {
        if (attackFrame == 0) {
            sprite.setTexture(textureLeftAttack1);
        }
        else {
            sprite.setTexture(textureLeftAttack2);
        }
    }
    for (const auto& bullet : bullets) {
        bullet.render(&window); // Przekazujemy wskaźnik na `window`
    }
    window.draw(sprite);
}

std::vector<Bullet>& Boss::getBullets() {
    return this->bullets;
}