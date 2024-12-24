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
			throw std::runtime_error("Nie mo¿na za³adowaæ tekstury przedmiotu: " + texturePath);
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
	std::vector<InventoryItem> items;   // Lista przedmiotów
	std::vector<std::shared_ptr<sf::Sprite>> eqItems;

	const int gridRows = 3;             // Iloœæ wierszy w siatce
	const int gridCols = 3;             // Iloœæ kolumn w siatce
	const float cellSize = 70.0f;       // Rozmiar kwadratów
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
	// Sprawdzenie czy aktualna pozycja myszy pokrywa siê ze sprite
	bool isMouseHover(const sf::Sprite& sprite, const sf::RenderWindow& window);



	void addItem(const std::string& texturePath, ItemType itemType) {
		// Oblicz pozycjê dla nowego przedmiotu
		int index = items.size();
		int row = index % gridCols;
		int col = index / gridCols;
		sf::Vector2f position = gridStart + sf::Vector2f(row * cellSize, col * cellSize);

	
		items.emplace_back(texturePath, position, itemType);
		std::shared_ptr<sf::Sprite> spritePtr = std::make_shared<sf::Sprite>(items.back().sprite);
		eqItems.emplace_back(spritePtr);
	}

	void removeItem(size_t index) {
		if (index >= eqItems.size()) {
			std::cerr << "Blad: Indeks poza zakresem!" << std::endl;
			return;
		}

		// Usuniêcie wskaŸnika z eqItems
		eqItems.erase(eqItems.begin() + index);

		// Usuniêcie odpowiadaj¹cego elementu z items
		items.erase(items.begin() + index);

		//Przesuñ pozosta³e elementy, aby zachowaæ spójnoœæ uk³adu
		updateItemPositions();
	}

	// Funkcja pomocnicza do aktualizacji pozycji elementów
	void updateItemPositions() {
		for (size_t i = 0; i < items.size(); ++i) {
			int row = i % gridCols;
			int col = i / gridCols;
			sf::Vector2f newPosition = gridStart + sf::Vector2f(row * cellSize, col * cellSize);
			items[i].sprite.setPosition(newPosition);
			eqItems[i]->setPosition(newPosition);
		}
	}



	ItemType getClickedItemType(sf::RenderWindow& window) {
		for (size_t i = 0; i < eqItems.size(); ++i) {
			if (isMouseHover(*eqItems[i], window) && sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
				return items[i].itemType; // Zwraca typ klikniêtego przedmiotu
			}
		}
		throw std::runtime_error("Nie klikniêto ¿adnego przedmiotu!");
	}

	void processClick(sf::RenderWindow& window,  Player& player ) {
		for (size_t i = 0; i < eqItems.size(); ++i) {
			if (isMouseHover(*eqItems[i], window) && sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
				ItemType type = items[i].itemType;
				std::cout << "Klikniêto przedmiot o typie: " << static_cast<int>(type) << std::endl;

				//player.setPlayerTexture("textury/las/");
				player.setEqTexture("textury/hat.png", "kapelusz");
				// Usuwanie przedmiotu
				removeItem(i);
				break;
			}
		}
	}


};

