#include "stdafx.h"
#include "Equipment.h"


Equipment::Equipment() {
	if (!eqTexture.loadFromFile("textury/eq.png")) {
		throw std::runtime_error("Nie mo¿na za³adowaæ tekstury ekwipunku: ");
	}
	eqSprite.setTexture(eqTexture);
	eqSprite.setPosition(sf::Vector2f(10.f, 70.f));
}

void Equipment::render(sf::RenderWindow& window) {
	if (isActive) {
		window.draw(eqSprite);

		// Rysowanie przedmiotów
		for (const auto& spritePtr : eqItems) {
			if (spritePtr) {
				window.draw(*spritePtr);
			}
		}
	}
}


// Zmiana koloru po najechaniu na dany sprite
void Equipment::handleHover(sf::RenderWindow& window, const std::vector<std::shared_ptr<sf::Sprite>>& items) {
	for (const auto& spritePtr : items) {
		// Jeœli kursor jest nad sprite'em, zmieñ kolor
		if (spritePtr && isMouseHover(*spritePtr, window)) {
			spritePtr->setColor(sf::Color::Blue); // Zmiana koloru na czerwony
		}
		else if (spritePtr) {
			spritePtr->setColor(sf::Color::White); // Przywróæ domyœlny kolor
		}
	}
}

bool Equipment::isMouseHover(const sf::Sprite& sprite, const sf::RenderWindow& window) {
	// Pobranie pozycji myszy w przestrzeni okna
	sf::Vector2i mousePos = sf::Mouse::getPosition(window);
	sf::FloatRect bounds = sprite.getGlobalBounds();

	// Sprawdzenie, czy pozycja myszy mieœci siê w granicach sprite'a
	return bounds.contains(static_cast<sf::Vector2f>(mousePos));
}


void Equipment::addItem(const std::string& texturePath, ItemType itemType) {
	// Oblicz pozycjê dla nowego przedmiotu
	int index = items.size();
	int row = index % gridCols;
	int col = index / gridCols;
	sf::Vector2f position = gridStart + sf::Vector2f(row * cellSize, col * cellSize);


	items.emplace_back(texturePath, position, itemType);
	std::shared_ptr<sf::Sprite> spritePtr = std::make_shared<sf::Sprite>(items.back().sprite);
	eqItems.emplace_back(spritePtr);
}

void Equipment::removeItem(size_t index) {
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


void Equipment::updateItemPositions() {
	for (size_t i = 0; i < items.size(); ++i) {
		int row = i % gridCols;
		int col = i / gridCols;
		sf::Vector2f newPosition = gridStart + sf::Vector2f(row * cellSize, col * cellSize);
		items[i].sprite.setPosition(newPosition);
		eqItems[i]->setPosition(newPosition);
	}
}

ItemType Equipment::getClickedItemType(sf::RenderWindow& window) {
	for (size_t i = 0; i < eqItems.size(); ++i) {
		if (isMouseHover(*eqItems[i], window) && sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
			return items[i].itemType; // Zwraca typ klikniêtego przedmiotu
		}
	}
	throw std::runtime_error("Nie klikniêto ¿adnego przedmiotu!");
}