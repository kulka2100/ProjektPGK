#pragma once
#include "stdafx.h"
#include "Background.h"
#include "Button.h"
#include "Menu.h"
#include "TextureManager.h"

/**
 * @brief Klasa odpowiedzialna za zarzadzanie mapami w menu gry, dziedziczy po klasach Button oraz Menu.
 * Umo¿liwia inicjalizacjê miniaturek map oraz ich wyœwietlanie.
 */
class Maps : public Button, Menu
{
private:
    std::vector <sf::Sprite> mapsItems; /**< Wektor przechowujacy sprite'y miniaturek map. */
    std::vector <sf::Texture> mapsTextures; /**< Wektor przechowujacy tekstury miniaturek map. */
    TextureManager textureManager; /**< Menedzer tekstur odpowiedzialny za zarzadzanie teksturami. */

public:
    /**
     * @brief Konstruktor klasy Maps, inicjalizuje obiekt Maps z tekstura.
     * @param filename Sciezka do pliku z tekstura.
     * @param width Szerokosc okna gry.
     */
    Maps(const std::string& filename, int width);

    /**
     * @brief Destruktor klasy Maps.
     */
    ~Maps() {}

    /**
     * @brief Inicjalizuje miniatureki map.
     * Ustawia tekstury i pozycje miniaturek map na podstawie szerokosci okna.
     * @param width Szerokosc okna gry.
     */
    void initMaps(int width);

    /**
     * @brief Zwraca referencje do wektora miniaturek map.
     * @return Referencja do wektora przechowujacego sprite'y miniaturek map.
     */
    std::vector <sf::Sprite>& getItems();

    /**
     * @brief Rysuje miniatureki map na oknie gry.
     * @param window Okno renderowania, na którym maj¹ zostaæ wyœwietlone elementy.
     */
    void draw(sf::RenderWindow& window);

};

