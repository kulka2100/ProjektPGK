#pragma once
#include "stdafx.h"
#include "Item.h"
#include "fstream"

enum class ItemType {
	Carrot,
	Health,
	Key,
	Chest,
	OpenChest,
	Tree,
	Hat,
	Wings,
	Saw
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


	CollectableItem();

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


	
	void save(std::ofstream& file) const {
		sf::Vector2f position = itemSprite.getPosition();
		file.write(reinterpret_cast<const char*>(&position.x), sizeof(position.x));
		file.write(reinterpret_cast<const char*>(&position.y), sizeof(position.y));
		file.write(reinterpret_cast<const char*>(&type), sizeof(type));
	}

	void load(std::ifstream& file) {
		sf::Vector2f position;
		file.read(reinterpret_cast<char*>(&position.x), sizeof(position.x));
		file.read(reinterpret_cast<char*>(&position.y), sizeof(position.y));
		file.read(reinterpret_cast<char*>(&type), sizeof(type));
	}

};

