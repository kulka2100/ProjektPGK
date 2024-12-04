#pragma once
#include "Enemy.h"
#include <cmath>

class Bats :
    public Enemy
{
private:
    void initTexture();
    float rotationAngle;
    float rotationBatSpeed;
    void update(float deltaTime) override;

public:
    Bats(sf::Vector2f startPosition, float speed, float leftBoundary, float rightBoundary);
    ~Bats();
};
