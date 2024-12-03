#pragma once
#include "Enemy.h"
class Moles :
    public Enemy
{
private:
    std::string getTexturePrefix() const override;
public:
    Moles(sf::Vector2f startPosition, float speed, float leftBoundary, float rightBoundary);
    ~Moles();
};

