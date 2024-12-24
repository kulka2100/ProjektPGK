#include "stdafx.h"
#include "Equipment.h"


Equipment::Equipment() {
	if (!eqTexture.loadFromFile("textury/eq.png")) {
		throw std::runtime_error("Nie mo�na za�adowa� tekstury ekwipunku: ");
	}
	eqSprite.setTexture(eqTexture);
	eqSprite.setPosition(sf::Vector2f(10.f, 70.f));
}

void Equipment::render(sf::RenderWindow& window) {
	if (isActive) {
		window.draw(eqSprite);

		// Rysowanie przedmiot�w
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
		// Je�li kursor jest nad sprite'em, zmie� kolor
		if (spritePtr && isMouseHover(*spritePtr, window)) {
			spritePtr->setColor(sf::Color::Blue); // Zmiana koloru na czerwony
		}
		else if (spritePtr) {
			spritePtr->setColor(sf::Color::White); // Przywr�� domy�lny kolor
		}
	}
}

bool Equipment::isMouseHover(const sf::Sprite& sprite, const sf::RenderWindow& window) {
	// Pobranie pozycji myszy w przestrzeni okna
	sf::Vector2i mousePos = sf::Mouse::getPosition(window);
	sf::FloatRect bounds = sprite.getGlobalBounds();

	// Sprawdzenie, czy pozycja myszy mie�ci si� w granicach sprite'a
	return bounds.contains(static_cast<sf::Vector2f>(mousePos));
}