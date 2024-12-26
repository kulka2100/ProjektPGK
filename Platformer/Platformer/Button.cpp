#include "stdafx.h"
#include "Button.h"


int Button::getHoverIndex(sf::RenderWindow& window, std::vector<sf::Sprite>& items) {
	for (size_t i = 0; i < items.size(); ++i) {
		if (isMouseHover(items[i], window)) {
			if (i < items.size()) { // Sprawdzanie zakresu
				std::cout << "Zaladowano mape o indeksie: " << i << std::endl;
			}
			else {
				std::cerr << "Blad: Indeks " << i << " poza zakresem mapsTextures!" << std::endl;
			}
			return i;	//Zwraca index Kliknietego elementu
		}
	}
}

//Zmiana koloru po najechaniu na dany sprite
void Button::handleHover(sf::RenderWindow& window, std::vector<sf::Sprite>& items) {
	for (auto& sprite : items) {
		// Jeœli kursor jest nad sprite'em, zmieñ kolor
		if (isMouseHover(sprite, window)) {
			sprite.setColor(sf::Color::Red); // Zmiana koloru na czerwony
		}
		else {
			sprite.setColor(sf::Color::White); // Przywróæ domyœlny kolor
		}
	}
	if (isMouseHover(backSprite, window)) {
		backSprite.setColor(sf::Color::Yellow);
	}
	else {
		backSprite.setColor(sf::Color(165, 42, 42));
	}
}
//Sprawdzenie czy akutalna pozycja myszy pokrwa sie ze sprite
bool Button::isMouseHover(const sf::Sprite& sprite, const sf::RenderWindow& window) {
	// Pobranie pozycji myszy w przestrzeni okna
	sf::Vector2i mousePos = sf::Mouse::getPosition(window);
	sf::FloatRect bounds = sprite.getGlobalBounds();

	// Sprawdzenie, czy pozycja myszy mieœci siê w granicach sprite'a
	return bounds.contains(static_cast<sf::Vector2f>(mousePos));
}