#include "stdafx.h"
#include "CollectableItem.h"

CollectableItem::CollectableItem(sf::Texture& colltectableTexture, sf::Vector2f position){
    // Ustawienie wskaŸnika do tekstury
    this->collectableItemTexture = &colltectableTexture;

    // Ustawienie tekstury w sprite
    if (this->collectableItemTexture) { // Sprawdzenie, czy wskaŸnik nie jest pusty
        itemSprite.setTexture(*this->collectableItemTexture);
    }

    // Ustawienie pozycji sprite'a
    this->itemSprite.setPosition(position);

}

