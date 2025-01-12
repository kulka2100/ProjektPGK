#pragma once
#include "Menu.h"
#include "Button.h"
#include "TextureManager.h"

/**
 * @brief Klasa reprezentuj¹ca ekran ustawieñ w grze.
 * Dziedziczy po klasach Button i Menu, umozliwiajac obs³uge interfejsu ustawien.
 */
class Settings : public Button, Menu
{
private:
	std::vector <sf::Sprite> settingsItems;		/**< Lista elementow ustawien */
	std::vector <sf::Texture> settingsTextures; /**< Lista tekstur wykorzystywanych w ekranie ustawien */
	TextureManager textureManager;

public:
	/**
	 * @brief Konstruktor klasy Settings.
	 * Inicjalizuje ekran ustawien, w tym ladowanie tekstur i elementow.
	 * @param width Szerokosc okna gry.
	 * @param height Wysokosc okna gry.
	 */
	Settings(float width, float height);

	/**
	 * @brief Zwraca referencje do listy elementow ustawien.
	 * Funkcja pozwala uzyskac dostep do listy sprite'ow reprezentujacych elementy ekranu ustawien.
	 * @return Referencja do listy elementow ustawien.
	 */
	std::vector <sf::Sprite>& getItems();

	/**
	 * @brief Rysuje ekran ustawien.
	 * Funkcja renderuje wszystkie elementy ekranu ustawien, w tym przyciski i tla.
	 * @param window Okno renderowania, w ktorym maja byc narysowane elementy ekranu ustawien.
	 */
	void draw(sf::RenderWindow& window);
};

