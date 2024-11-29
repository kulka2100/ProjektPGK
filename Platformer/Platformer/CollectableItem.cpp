#include "stdafx.h"
#include "CollectableItem.h"

CollectableItem::CollectableItem(sf::Texture& colltectableTexture, sf::Vector2f position){
    // Ustawienie wska�nika do tekstury
    this->collectableItemTexture = &colltectableTexture;

    // Ustawienie tekstury w sprite
    if (this->collectableItemTexture) { // Sprawdzenie, czy wska�nik nie jest pusty
        itemSprite.setTexture(*this->collectableItemTexture);
    }

    // Ustawienie pozycji sprite'a
    this->itemSprite.setPosition(position);

}

