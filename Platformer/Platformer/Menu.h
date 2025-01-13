#pragma once
#include "Background.h"

/**
 * @brief Klasa odpowiedzialna za zarzadzanie menu w grze.
 * Umozliwia rysowanie menu, nawigowanie po elementach oraz wybor.
 */
class Menu
{
protected:
    sf::Font font;                                      /**< Czcionka u¿ywana w menu. */
    std::vector<sf::Text> menuItems;                    /**< Wektor przechowuj¹cy elementy tekstowe menu. */
    int selectedIndex;                                  /**< Indeks aktualnie wybranego elementu w menu. */
    const sf::Color selectedColor = sf::Color::Red;     /**< Kolor zaznaczonego elementu menu. */
    const sf::Color unselectedColor = sf::Color::White; /**< Kolor niezaznaczonego elementu menu. */
    Background* background;                             /**< T³o menu. */

public:
    /**
     * @brief Konstruktor klasy Menu, inicjalizuje menu na podstawie szerokosci i wysokosci okna.
     * @param width Szerokosc okna gry.
     * @param height Wysokosc okna gry.
     */
    Menu(float width, float height);

    /**
     * @brief Konstruktor domyslny klasy Menu.
     */
    Menu();

    /**
     * @brief Destruktor klasy Menu, zwalnia zasoby.
     */
    ~Menu() {
        delete background;
    }

    /**
     * @brief Rysuje menu na ekranie gry.
     * @param window Okno renderowania, na którym ma zostaæ wyœwietlone menu.
     */
    void draw(sf::RenderWindow& window);

    /**
     * @brief Przemieszcza zaznaczenie menu w górê.
     */
    void moveUp();

    /**
     * @brief Przemieszcza zaznaczenie menu w dó³.
     */
    void moveDown();

    /**
     * @brief Zwraca indeks aktualnie wybranego elementu w menu.
     * @return Indeks aktualnie wybranego elementu.
     */
    int getSelectedIndex() const;
};

