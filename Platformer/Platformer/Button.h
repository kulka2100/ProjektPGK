#pragma once
#include "TextureManager.h"

/**
 * @brief Klasa reprezentujaca przycisk w grze.
 * Zawiera funkcje do obslugi najechania na przycisk, sprawdzania klikniecia i zmiany koloru.
 */
class Button
{
protected:
	sf::Sprite backSprite; ///< Sprite reprezentujacy tlo przycisku.
public:
	/**
	* @brief Metoda zwracajaca indeks kliknietego elementu.
	* Sprawdza, ktory element zostal klikniety na podstawie pozycji myszy.
	* @param window Okno gry.
	* @param items Wektor sprite'ow reprezentujacych elementy, na ktore mozna kliknac.
	* @return Indeks kliknietego elementu.
	*/
	int getHoverIndex(sf::RenderWindow& window, std::vector<sf::Sprite>& items);

	/**
	* @brief Zmienia kolor przycisku po najechaniu na dany sprite.
	* Zmienia wyglad przycisku, np. zmienia kolor tla po najechaniu kursorem.
	* @param window Okno gry.
	* @param items Wektor sprite'ow, ktore odpowiadaja przyciskom.
	*/
	void handleHover(sf::RenderWindow& window, std::vector<sf::Sprite>& items);

	/**
	* @brief Sprawdza, czy aktualna pozycja myszy pokrywa sie ze sprite.
	* Ustala, czy kursor myszy znajduje sie nad danym przyciskiem.
	* @param sprite Sprite, na ktorym sprawdzany jest kursor.
	* @param window Okno gry.
	* @return Zwraca true, jesli kursor znajduje sie nad przyciskiem, w przeciwnym razie false.
	*/
	bool isMouseHover(const sf::Sprite& sprite, const sf::RenderWindow& window);
};

