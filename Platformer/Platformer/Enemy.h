#pragma once
#include <SFML/Graphics.hpp>
#include <iostream>

class Enemy {
private:
    sf::Sprite sprite;
    std::vector<sf::Texture> rightTextures;
    std::vector<sf::Texture> leftTextures;
    float animationTimer;
    float animationTimerMax;
    unsigned int animationIndex;
    sf::Vector2f position;
    float speed;
    float direction;
    const float GROUND_Y = 480.0f;

    float leftBoundary;
    float rightBoundary;

    void initSprite();
    void initTexture();

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
};