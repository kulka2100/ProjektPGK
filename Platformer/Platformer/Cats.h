#pragma once
#include "Enemy.h"
class Cats :
    public Enemy
{
private:
    void initTexture();

public:
    Cats(sf::Vector2f startPosition, float speed, float leftBoundary, float rightBoundary);
    ~Cats();
};

