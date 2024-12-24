#pragma once
#include <SFML/Graphics.hpp>
#include <iostream>
#include <fstream>

class Enemy {
private:

    sf::Clock attackClock;


    sf::Clock damageClock;
    float damageInterval;


    static const float GROUND_Y;






    float deathAnimationSpeed = 200.f;

    float deathTimer = 0.0f; // Licznik czasu animacji œmierci
    sf::Vector2f velocity; // Prêdkoœæ ruchu wroga podczas œmierci
    float rotationSpeed = 0.0f; // Prêdkoœæ obracania siê wroga

protected:
    int attackFrame;
    bool facingRight;
    unsigned int animationIndex;
    float speed;
    float direction;
    float animationTimer;
    float animationTimerMax;
    float leftBoundary;
    float rightBoundary;
    bool isDying = false;
    bool isAttacking;
    sf::Vector2f position;
    sf::Sprite sprite;
    std::vector<sf::Texture> rightTextures;
    std::vector<sf::Texture> leftTextures;
    int health;
    sf::Texture textureRightAttack1;
    sf::Texture textureRightAttack2;
    sf::Texture textureLeftAttack1;
    sf::Texture textureLeftAttack2;
    void initSprite();

public:
    Enemy(sf::Vector2f startPosition, float speed, float leftBoundary, float rightBoundary);
    ~Enemy();


    // Metody
    virtual void update(float deltaTime);
    virtual void render(sf::RenderWindow& window);

    // Gettery
    sf::FloatRect getBounds() const;
    sf::Vector2f getPosition() const;

    std::vector<sf::Texture>& getRightTextures() {
        return rightTextures;
    }
    std::vector<sf::Texture>& getLeftTextures() {
        return leftTextures;
    }


    // Settery
    void setPosition(const sf::Vector2f& newPosition);
    void setDirection(const sf::Vector2f& newDirection);

    void save(std::ofstream& file) const {
        // Zapisujemy pozycję
        file.write(reinterpret_cast<const char*>(&position.x), sizeof(position.x));
        file.write(reinterpret_cast<const char*>(&position.y), sizeof(position.y));

        // Zapisujemy zdrowie
        file.write(reinterpret_cast<const char*>(&health), sizeof(health));

        // Zapisujemy prędkość
        file.write(reinterpret_cast<const char*>(&speed), sizeof(speed));

        // Zapisujemy kierunek
        file.write(reinterpret_cast<const char*>(&direction), sizeof(direction));

        // Zapisujemy granice ruchu
        file.write(reinterpret_cast<const char*>(&leftBoundary), sizeof(leftBoundary));
        file.write(reinterpret_cast<const char*>(&rightBoundary), sizeof(rightBoundary));

        // Zapisujemy czy wróg jest w trybie ataku
        file.write(reinterpret_cast<const char*>(&isAttacking), sizeof(isAttacking));

        // Zapisujemy czy wróg jest w trakcie animacji śmierci
        file.write(reinterpret_cast<const char*>(&isDying), sizeof(isDying));
    }




    void load(std::ifstream& file) {
        // Odczytujemy pozycję
        file.read(reinterpret_cast<char*>(&position.x), sizeof(position.x));
        file.read(reinterpret_cast<char*>(&position.y), sizeof(position.y));
        sprite.setPosition(position); // Aktualizujemy pozycję sprite'a

        // Odczytujemy zdrowie
        file.read(reinterpret_cast<char*>(&health), sizeof(health));

        // Odczytujemy prędkość
        file.read(reinterpret_cast<char*>(&speed), sizeof(speed));

        // Odczytujemy kierunek
        file.read(reinterpret_cast<char*>(&direction), sizeof(direction));

        // Odczytujemy granice ruchu
        file.read(reinterpret_cast<char*>(&leftBoundary), sizeof(leftBoundary));
        file.read(reinterpret_cast<char*>(&rightBoundary), sizeof(rightBoundary));

        // Odczytujemy czy wróg jest w trybie ataku
        file.read(reinterpret_cast<char*>(&isAttacking), sizeof(isAttacking));

        // Odczytujemy czy wróg jest w trakcie animacji śmierci
        file.read(reinterpret_cast<char*>(&isDying), sizeof(isDying));

    }


    void setTextures(const std::vector<sf::Texture>& right, const std::vector<sf::Texture>& left) {
        this->rightTextures = right;
        this->leftTextures = left;

        // Ustawienie domyślnej tekstury, jeśli są dostępne
        if (!rightTextures.empty()) {
            this->sprite.setTexture(rightTextures[0]);
        }
        else if (!leftTextures.empty()) {
            this->sprite.setTexture(leftTextures[0]);
        }
    }

    void startAttack();
    void updateAttack();
    void resetAttack();
    bool getIsAttacking() const;
    bool canDealDamage();
    void move(float offsetX);
    float getLeftBoundary() const;
    float getRightBoundary() const;
    void setBoundaries(float left, float right);
    void reduceHealth(int damage);
    int getHealth() const;
    bool updateDeathAnimation(float deltaTime);
    void startDeathAnimation();
    bool isDead() const;
};