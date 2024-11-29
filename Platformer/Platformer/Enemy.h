#pragma once
#include <SFML/Graphics.hpp>
#include <iostream>

class Enemy {
private:
    sf::Sprite sprite;
    std::vector<sf::Texture> rightTextures;
    std::vector<sf::Texture> leftTextures;
    sf::Texture textureRightAttack1;
    sf::Texture textureRightAttack2;
    sf::Texture textureLeftAttack1;
    sf::Texture textureLeftAttack2;
    bool facingRight;
    sf::Clock attackClock;
    bool isAttacking;
    int attackFrame;
    sf::Clock damageClock; 
    float damageInterval;
    float animationTimer;
    float animationTimerMax;
    unsigned int animationIndex;
    sf::Vector2f position;
    float speed;
    float direction;
    static const float GROUND_Y;

    float leftBoundary;
    float rightBoundary;

    void initSprite();
    void initTexture();

    int health = 3;
    float deathAnimationSpeed = 200.f;
    bool isDying = false; // Flaga oznaczaj�ca, �e wr�g umiera
    float deathTimer = 0.0f; // Licznik czasu animacji �mierci
    sf::Vector2f velocity; // Pr�dko�� ruchu wroga podczas �mierci
    float rotationSpeed = 0.0f; // Pr�dko�� obracania si� wroga

public:
    Enemy(sf::Vector2f startPosition, float speed, float leftBoundary, float rightBoundary);
    ~Enemy();


    // Metody
    void update(float deltaTime);
    void render(sf::RenderWindow& window);

    // Gettery
    sf::FloatRect getBounds() const;
    sf::Vector2f getPosition() const;

    // Settery
    void setPosition(const sf::Vector2f& newPosition);
    void setDirection(const sf::Vector2f& newDirection);

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