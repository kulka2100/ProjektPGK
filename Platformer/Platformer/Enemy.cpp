#include "stdafx.h"
#include "Enemy.h"




Enemy::Enemy(sf::Vector2f startPosition, float speed, float leftBoundary, float rightBoundary)
    : position(startPosition), speed(speed), leftBoundary(leftBoundary), rightBoundary(rightBoundary), direction(1.0f), facingRight(true) {
    this->initSprite();
    this->animationTimer = 0.0f;
    this->animationTimerMax = 0.2f;
    this->animationIndex = 0;
    this->damageInterval = 0.5f;
    this->isAttacking = false;
    this->attackFrame = 0;
}

Enemy::~Enemy() {}

void Enemy::initSprite() {
    if (!rightTextures.empty()) {
        this->sprite.setTexture(rightTextures[0]); // Ustawienie domyslnej tekstury
    }
    else {
        std::cerr << "(klasa Enemy)Brak tekstur w wektorze rightTextures podczas inicjalizacji sprite'a!" << std::endl;
    }
    this->sprite.setPosition(this->position);
}

void Enemy::update(float deltaTime) {
    if (this->isDying) {
        this->updateDeathAnimation(deltaTime);
        return; // Nie wykonuj standardowych operacji ruchu
    }
    if (isAttacking) {
        this->updateAttack();
        return;
    }

    // Obs³uga animacji chodzenia
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
        this->facingRight = true;
    }
    else if (this->position.x >= this->rightBoundary) {
        this->direction = -1.0f;
        this->facingRight = false;
    }

    // Zaktualizuj pozycjê sprite'a (bez wymuszania pozycji Y)
    this->sprite.setPosition(this->position);
}

void Enemy::render(sf::RenderWindow& window) {
    if (isAttacking) {
        if (attackFrame == 0) {
            if (this->facingRight) {
                sprite.setTexture(textureRightAttack1);
            }
            else {
                sprite.setTexture(textureLeftAttack1);
            }
        }
        else {
            if (this->facingRight) {
                sprite.setTexture(textureRightAttack2);
            }
            else {
                sprite.setTexture(textureLeftAttack2);
            }
        }
    }
    window.draw(sprite);
}

sf::FloatRect Enemy::getBounds() const {
    return this->sprite.getGlobalBounds();
}



void Enemy::startAttack() {
    this->isAttacking = true;
    this->attackClock.restart();
}

void Enemy::updateAttack() {
    if (isAttacking) {
        if (attackClock.getElapsedTime().asSeconds() > 0.2f) { // Co 0.2 sekundy zmiana klatki
            attackFrame = (attackFrame + 1) % 2; // 2 klatki animacji
            attackClock.restart();
        }
    }
}

void Enemy::resetAttack() {
    this->isAttacking = false;
    this->attackFrame = 0;
}

bool Enemy::getIsAttacking() const {
    return this->isAttacking;
}

bool Enemy::canDealDamage() {
    // Sprawdzanie, czy min¹³ czas od ostatniego zadania obra¿eñ
    if (damageClock.getElapsedTime().asSeconds() >= damageInterval) {
        damageClock.restart();
        return true;
    }
    return false;
}

void Enemy::move(float offsetX) {
    this->position.x += offsetX;
    this->sprite.setPosition(this->position); // Aktualizuj pozycjê sprite'a
}

float Enemy::getLeftBoundary() const {
    return this->leftBoundary;
}

float Enemy::getRightBoundary() const {
    return this->rightBoundary;
}

void Enemy::setBoundaries(float left, float right) {
    this->leftBoundary = left;
    this->rightBoundary = right;
}

void Enemy::reduceHealth(int damage) {
    this->health -= damage;
    if (this->health <= 0) {
        this->health = 0;
        this->isDying = true; 
    }
}

int Enemy::getHealth() const {
    return this->health;
}


bool Enemy::updateDeathAnimation(float deltaTime) {
    if (!this->isDying) return false;

    // Animacja obracania
    this->sprite.rotate(this->rotationSpeed * deltaTime);

    // Ruch w dó³
    this->sprite.move(0.f, this->velocity.y * deltaTime);

    // Jeœli wróg opuœci ekran, zwróæ true, aby mo¿na go by³o usun¹æ
    if (this->sprite.getPosition().y > 600.f) { // Dolna krawêdŸ ekranu
        return true;
    }
    return false;
}

void Enemy::startDeathAnimation() {
    this->isDying = true; // Flaga oznaczaj¹ca, ¿e wróg umiera
    this->velocity = sf::Vector2f(0.0f, 150.0f); // Prêdkoœæ opadania wroga w dó³
    this->rotationSpeed = 90.0f; // Prêdkoœæ obracania siê (stopnie na sekundê)
}

bool Enemy::isDead() const {
    return isDying;
}