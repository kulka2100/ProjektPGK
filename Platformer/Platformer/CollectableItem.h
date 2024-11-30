#pragma once
#include "stdafx.h"
#include "Item.h"

enum class ItemType {
	Carrot,
	Health,
};

class CollectableItem : public Item
{
private:
	sf::Texture *collectableItemTexture;
	ItemType type;
	bool isCollected = false;

public:

	CollectableItem(sf::Texture& obstacleTexture, sf::Vector2f position, ItemType itemType);

	sf::Texture& getTexture() override;

	void setIsCollected(bool isCollected);

	bool getIsCollected() const;

	ItemType getType() const;

};

