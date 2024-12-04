#pragma once
#include <SFML/Graphics.hpp>
#include <iostream>

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