#pragma once
#include "stdafx.h"
class Item
{
protected:
	sf::Sprite itemSprite;
public:
public:
    virtual sf::FloatRect getBounds() {
        return itemSprite.getGlobalBounds();
    }

    virtual sf::Vector2f getPosition() {
        return itemSprite.getPosition();
    }

    virtual void update(sf::Vector2f pos) {
        itemSprite.move(pos); // Bazowa logika ruchu
    }

    virtual void render(sf::RenderWindow& window) {
        window.draw(itemSprite); // Bazowa logika renderowania
    }

    virtual sf::Sprite& getSprite() {
        return itemSprite;
    }

    virtual sf::Texture& getTexture() = 0; // To wymaga implementacji w klasach pochodnych

    virtual ~Item() = default;
};

