#pragma once
#include "stdafx.h"
#include "Item.h"
#include "fstream"

/**
 * @brief Typy przedmiotow, ktore moga byc zbierane przez gracza.
 */
enum class ItemType {
	Carrot,
	Health,
	Key,
	Chest,
	OpenChest,
	Tree,
	Hat,
	Wings,
	Saw,
	Gate,
	Helmet,
	None
};

/**
 * @brief Klasa reprezentujaca przedmioty, ktore gracz moze zbierac w grze.
 * Przedmioty te moga byc takie jak marchewka, zdrowie, klucz itp.
 */
class CollectableItem : public Item
{
private:
	sf::Texture* collectableItemTexture; ///< Tekstura przedmiotu.
	ItemType type;                       ///< Typ przedmiotu.
	bool isCollected = false;            ///< Flaga wskazujaca, czy przedmiot zostal zebrany.
	bool isChestOpen = false;            ///< Flaga wskazujaca, czy skrzynia zostala otwarta.
	std::vector<sf::Sprite> carrots;     ///< Wektor sprite'ow reprezentujacych marchewki.
public:
	/**
	 * @brief Konstruktor klasy CollectableItem.
	 * Inicjalizuje przedmiot z tekstura, pozycja oraz typem.
	 * @param obstacleTexture Tekstura przedmiotu.
	 * @param position Pozycja przedmiotu.
	 * @param itemType Typ przedmiotu.
	 */
	CollectableItem(sf::Texture& obstacleTexture, sf::Vector2f position, ItemType itemType);

	/**
	 * @brief Konstruktor domyslny klasy CollectableItem.
	 */
	CollectableItem();

	/**
	 * @brief Zwraca teksture przedmiotu.
	 * @return Referencja do tekstury przedmiotu.
	 */
	sf::Texture& getTexture() override;

	/**
	 * @brief Ustawia typ przedmiotu.
	 * @param newType Nowy typ przedmiotu.
	 */
	void setType(ItemType newType) {
		this->type = newType;
	}

	/**
	 * @brief Ustawia teksture przedmiotu.
	 * @param newTexture Nowa tekstura.
	 */
	void setTexture(const sf::Texture& newTexture) {
		this->itemSprite.setTexture(newTexture);
	}

	/**
	 * @brief Ustawia, czy przedmiot zostal zebrany.
	 * @param isCollected Flaga wskazujaca, czy przedmiot jest zebrany.
	 */
	void setIsCollected(bool isCollected);

	/**
	 * @brief Zwraca, czy przedmiot zostal zebrany.
	 * @return Zwraca true, jesli przedmiot zostal zebrany, w przeciwnym razie false.
	 */
	bool getIsCollected() const;
	
	/**
	 * @brief Zwraca typ przedmiotu.
	 * @return Typ przedmiotu.
	 */
	ItemType getType() const;

	/**
	 * @brief Ustawia, czy skrzynia zostala otwarta.
	 * @param isOpen Flaga wskazujaca, czy skrzynia jest otwarta.
	 */
	void setIsOpenChest(bool isOpen) {
		this->isChestOpen = isOpen;
	}

	/**
	 * @brief Zwraca, czy skrzynia jest otwarta.
	 * @return Zwraca true, jesli skrzynia jest otwarta, w przeciwnym razie false.
	 */
	bool getIsChestOpen() {
		return isChestOpen;
	}

};

