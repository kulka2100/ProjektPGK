#include "stdafx.h"
#include "Moles.h"


Moles::Moles(sf::Vector2f startPosition, float speed, float leftBoundary, float rightBoundary)
    : Enemy(startPosition, speed, leftBoundary, rightBoundary) {
    this->health = 3;

}



Moles::~Moles() {}

std::string Moles::getTexturePrefix() const {
    return "mole";  
}
