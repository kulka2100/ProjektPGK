#pragma once
#include "stdafx.h"
#include "CollectableItem.h"
#include "Player.h"

/**
 * @brief Struktura przechowujaca informacje o przedmiocie w ekwipunku.
 * Zawiera teksture, sprite oraz typ przedmiotu.
 */
struct InventoryItem{
	std::shared_ptr<sf::Texture> texture; ///< Wskaznik do tekstury przedmiotu.
	sf::Sprite sprite;					  ///< Sprite przedmiotu.
	ItemType itemType;					  ///< Typ przedmiotu.

	/**
	 * @brief Konstruktor struktury InventoryItem.
	 * @param texturePath Sciezka do pliku tekstury.
	 * @param position Pozycja, w ktorej ma byc umieszczony sprite.
	 * @param itemType Typ przedmiotu.
	 */
	InventoryItem(const std::string& texturePath, const sf::Vector2f& position, ItemType itemType) : itemType(itemType) {
		texture = std::make_shared<sf::Texture>();
		if (!texture->loadFromFile(texturePath)) {
			throw std::runtime_error("Nie mo¿na za³adowaæ tekstury przedmiotu: " + texturePath);
		}
		sprite.setTexture(*texture);
		sprite.setPosition(position);
	}
};


/**
 * @brief Klasa reprezentujaca ekwipunek gracza.
 * Zawiera liste przedmiotow, obsluge ich pozycji oraz interakcje z przedmiotami w ekwipunku.
 */
class Equipment :  public CollectableItem
{
private:
	sf::Texture eqTexture; ///< Tekstura dla ekwipunku.
	sf::Sprite eqSprite; ///< Sprite reprezentujacy ekwipunek.
	bool isActive; ///< Flaga aktywacji ekwipunku.
	std::vector<InventoryItem> items;   ///< Lista przedmiotow w ekwipunku.
	std::vector<std::shared_ptr<sf::Sprite>> eqItems; ///< Lista sprite'ow przedmiotow w ekwipunku.

	const int gridRows = 3;             ///< Ilosc wierszy w siatce ekwipunku.
	const int gridCols = 3;             ///< Ilosc kolumn w siatce ekwipunku.
	const float cellSize = 70.0f;       ///< Rozmiar komorek w siatce ekwipunku.
	const sf::Vector2f gridStart = { 90.0f, 230.0f }; ///< Poczatkowa pozycja siatki ekwipunku.

public:
	/**
	 * @brief Konstruktor klasy Equipment.
	 * Inicjalizuje stan ekwipunku i ustawia poczatkowe wartosci.
	 */
	Equipment();

	/**
	 * @brief Zwraca informacje, czy ekwipunek jest aktywny.
	 * @return Flaga aktywnego ekwipunku.
	 */
	bool getIsActive() {
		return isActive;
	}

	/**
	 * @brief Zwraca liste przedmiotow w ekwipunku.
	 * @return Referencja do wektora sprite'ow przedmiotow w ekwipunku.
	 */
	const std::vector<std::shared_ptr<sf::Sprite>>& getEqItems() const {
		return eqItems;
	}

	/**
	  * @brief Ustawia stan aktywacji ekwipunku.
	  * @param isActive Nowy stan aktywacji ekwipunku.
	  */
	void setIsActive(bool isActive) {
		this->isActive = isActive;
	}

	/**
	  * @brief Renderuje ekwipunek na ekranie.
	  * @param window Okno gry, w ktorym rysowany jest ekwipunek.
	  */
	void render(sf::RenderWindow& window);

	/**
	 * @brief Zmienia kolor sprite'a po najechaniu mysza.
	 * @param window Okno gry.
	 * @param items Lista sprite'ow przedmiotow w ekwipunku.
	 */
	void handleHover(sf::RenderWindow& window, const std::vector<std::shared_ptr<sf::Sprite>>& items);

	/**
	  * @brief Sprawdza, czy pozycja myszy pokrywa sie ze sprite'em.
	  * @param sprite Sprite, z ktorym ma byc porownana pozycja myszy.
	  * @param window Okno gry.
	  * @return Flaga, czy myszy pokrywa sie ze sprite'em.
	  */
	bool isMouseHover(const sf::Sprite& sprite, const sf::RenderWindow& window);

	/**
	 * @brief Dodaje nowy przedmiot do ekwipunku.
	 * @param texturePath Sciezka do tekstury przedmiotu.
	 * @param itemType Typ przedmiotu.
	 */
	void addItem(const std::string& texturePath, ItemType itemType);

	/**
	 * @brief Aktualizuje pozycje przedmiotow w ekwipunku.
	 */
	void updateItemPositions();

	/**
	 * @brief Usuwa przedmiot z ekwipunku.
	 * @param index Indeks przedmiotu do usuniecia.
	 */
	void removeItem(size_t index);

	/**
	 * @brief Sprawdza typ przedmiotu kliknietego przez gracza.
	 * @param window Okno gry.
	 * @return Typ przedmiotu, na ktorym kliknal gracz.
	 */
	ItemType getClickedItemType(sf::RenderWindow& window);

	/**
	 * @brief Procesuje klikniecie myszy w ekwipunku i wykonuje akcje.
	 * @param window Okno gry.
	 * @param player Gracz, z ktorym wiaze sie akcja.
	 */
	void processClick(sf::RenderWindow& window, Player& player);
	
	/**
	 * @brief Resetuje przedmioty w ekwipunku.
	 */
	void resetItems();

};

