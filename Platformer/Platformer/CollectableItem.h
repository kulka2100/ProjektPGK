#pragma once
#include "stdafx.h"
#include "Item.h"

class CollectableItem : public Item
{
private:
	sf::Texture *collectableItemTexture;
	bool isCollected = false;
public:

	CollectableItem(sf::Texture& obstacleTexture, sf::Vector2f position);

	sf::Texture& getTexture() override {
		return *collectableItemTexture;
	}

	void setIsCollected(bool isCollected) {
		this->isCollected = isCollected;
	}

	bool getIsCollected() const {
		return isCollected;
	}

};

