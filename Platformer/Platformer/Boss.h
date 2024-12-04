#pragma once
#include "Enemy.h"
#include "Bullet.h"
#include <random>
class Boss :
    public Enemy
{
private:
    void initTexture();
    void update(float deltaTime) override;
    void render(sf::RenderWindow& window) override;
    float jumpTimer;
    bool isJumping;
    float jumpTime;
    float jumpDuration;
    sf::Texture bulletTexture;
    std::vector<Bullet> bullets; 
    float shootTimer = 0.0f; 
    float shootInterval = 1.0f; 
    float bulletSpeed = 300.0f; 

public:
    Boss(sf::Vector2f startPosition, float speed, float leftBoundary, float rightBoundary);
    ~Boss();
    std::vector<Bullet>& getBullets();
};

