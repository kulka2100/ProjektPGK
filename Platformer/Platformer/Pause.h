#pragma once
#include "stdafx.h"
#include "Background.h"
#include "TextureManager.h"
#include "Button.h"

/**
 * @brief Klasa reprezentujaca ekran pauzy w grze.
 * Klasa ta rozszerza klase Button i dodaje funkcjonalnosc pauzy,
 * w tym wyswietlanie menu pauzy z opcjami kontynuacji gry.
 */
class Pause : public Button
{
private:
    sf::Font font;                      /**< Czcionka do wyswietlania tekstu. */
    Background* background;             /**< Tlo ekranu pauzy. */
    sf::Texture playTexture;            /**< Tekstura dla przycisku 'Play'. */
    sf::Texture saveTexture;            /**< Tekstura dla przycisku 'Zapis'. */
    sf::Sprite backSprite;              /**< Sprite tla dla ekranu pauzy. */
    sf::Texture backTexture;            /**< Tekstura tla dla ekranu pauzy. */
    std::vector<sf::Sprite> pauseItems; /**< Lista elementow menu pauzy. */

	/**
    * @brief Inicjalizuje elementy menu pauzy.
    * Funkcja ustawia tekstury i pozycje dla elementow interfejsu pauzy.
    */
	void initItems();

public:
    /**
        * @brief Konstruktor klasy Pause.
        * Inicjalizuje ekran pauzy z odpowiednimi ustawieniami.
        * @param width Szerokosc okna gry.
        * @param height Wysokosc okna gry.
        */
    Pause(float width, float height);

    /**
     * @brief Destruktor klasy Pause.
     * Zwalnia zasoby, w tym obiekt Background.
     */
    ~Pause() {
        delete background;
    }

    /**
     * @brief Rysuje ekran pauzy.
     * Funkcja renderuje wszystkie elementy ekranu pauzy, w tym tla i przyciski.
     * @param window Okno renderowania, w ktorym ma byc narysowany ekran pauzy.
     */
    void draw(sf::RenderWindow& window);

    /**
     * @brief Zwraca wektor elementow pauzy.
     * @return Wejscia w menu pauzy, takie jak przyciski, tlo, itp.
     */
    std::vector<sf::Sprite>& getPauseItems();

};

