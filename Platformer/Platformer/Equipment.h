#pragma once
#include "stdafx.h"
#include "CollectableItem.h"
#include "Player.h"


struct InventoryItem{
	std::shared_ptr<sf::Texture> texture;
	sf::Sprite sprite;
	ItemType itemType;

	InventoryItem(const std::string& texturePath, const sf::Vector2f& position, ItemType itemType) : itemType(itemType) {
		texture = std::make_shared<sf::Texture>();
		if (!texture->loadFromFile(texturePath)) {
			throw std::runtime_error("Nie mo�na za�adowa� tekstury przedmiotu: " + texturePath);
		}
		sprite.setTexture(*texture);
		sprite.setPosition(position);
	}
};

class Equipment :  public CollectableItem
{
private:
	sf::Texture eqTexture;
	sf::Sprite eqSprite;
	bool isActive;
	std::vector<InventoryItem> items;   // Lista przedmiot�w
	std::vector<std::shared_ptr<sf::Sprite>> eqItems;

	const int gridRows = 3;             // Ilo�� wierszy w siatce
	const int gridCols = 3;             // Ilo�� kolumn w siatce
	const float cellSize = 70.0f;       // Rozmiar kwadrat�w
	const sf::Vector2f gridStart = { 90.0f, 230.0f }; // Pozycja startowa siatki

public:
	Equipment();

	bool getIsActive() {
		return isActive;
	}
	const std::vector<std::shared_ptr<sf::Sprite>>& getEqItems() const {
		return eqItems;
	}

	void setIsActive(bool isActive) {
		this->isActive = isActive;
	}
	void render(sf::RenderWindow& window);
	// Zmiana koloru po najechaniu na dany sprite
	void handleHover(sf::RenderWindow& window, const std::vector<std::shared_ptr<sf::Sprite>>& items);
	// Sprawdzenie czy aktualna pozycja myszy pokrywa si� ze sprite
	bool isMouseHover(const sf::Sprite& sprite, const sf::RenderWindow& window);

	void addItem(const std::string& texturePath, ItemType itemType);

	// Funkcja do aktualizacji pozycji element�w
	void updateItemPositions();

	void removeItem(size_t index);

	ItemType getClickedItemType(sf::RenderWindow& window);

	void processClick(sf::RenderWindow& window, Player& player) {
		static bool mouseHeld = false; // �ledzenie stanu przycisku myszy

		if (sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
			if (!mouseHeld) {
				mouseHeld = true; //przycisk zosta� wcisniety

				for (size_t i = 0; i < eqItems.size(); ++i) {
					if (isMouseHover(*eqItems[i], window)) {
						ItemType type = items[i].itemType;
						std::cout << "Klikni�to przedmiot o typie: " << static_cast<int>(type) << std::endl;

						switch (type) {
						case ItemType::Hat:
							player.setEqTexture("textury/hat.png", "kapelusz", type);
							break;
						case ItemType::Wings:
							player.setEqTexture("textury/wings.png", "skrzydla", type);
							break;

						case ItemType::Saw:
							player.setEqTexture("textury/saw.png", "pila", type);
						}

						// Usuwanie przedmiotu
						removeItem(i);

						// Przerwanie p�tli po obs�u�eniu klikni�cia
						break;
					}
				}
			}
		}
		else {
			mouseHeld = false; // Resetujemy stan przycisku po jego puszczeniu
		}
	}

};

