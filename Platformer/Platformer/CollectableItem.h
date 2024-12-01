#pragma once
#include "stdafx.h"
#include "Item.h"

enum class ItemType {
	Carrot,
	Health,
	Key,
	Chest,
	OpenChest,
	Tree,
};

class CollectableItem : public Item
{
private:
	sf::Texture *collectableItemTexture;
	ItemType type;
	bool isCollected = false;
	bool isChestOpen = false;
	// Powi¹zane obiekty (np. marchewki dla drzewa)
	std::vector<sf::Sprite> carrots;
public:

	CollectableItem(sf::Texture& obstacleTexture, sf::Vector2f position, ItemType itemType);

	sf::Texture& getTexture() override;

	void setType(ItemType newType) {
		this->type = newType;
	}

	void setTexture(const sf::Texture& newTexture) {
		this->itemSprite.setTexture(newTexture);
	}

	void setIsCollected(bool isCollected);

	bool getIsCollected() const;

	ItemType getType() const;

	void setIsOpenChest(bool isOpen) {
		this->isChestOpen = isOpen;
	}

	bool getIsChestOpen() {
		return isChestOpen;
	}

};

