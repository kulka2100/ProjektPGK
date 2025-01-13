#pragma once
#include <SFML/Graphics.hpp>
#include <vector>

/**
 * @brief Klasa reprezentujaca menu statystyk w grze.
 * Umozliwia nawigowanie po opcjach menu oraz ich renderowanie.
 */
class StatsMenu {
private:
    std::vector<sf::Text> options; /**< Opcje menu */
    int selectedIndex;             /**< Aktualnie wybrana opcja */
    sf::Font font;                 /**< Czcionka uzywana w menu */

public:
    /**
     * @brief Konstruktor klasy StatsMenu.
     * Inicjalizuje menu statystyk, wczytujac odpowiednia czcionke.
     * @param font Czcionka uzywana do rysowania tekstu w menu.
     */
    explicit StatsMenu(const sf::Font& font);

    /**
     * @brief Rysuje menu statystyk.
     * Renderuje wszystkie elementy menu, w tym opcje.
     * @param window Okno renderowania, w ktorym maja byc narysowane elementy menu.
     */
    void draw(sf::RenderWindow& window);

    /**
     * @brief Przesuwa wybór menu w górê.
     * Funkcja zmienia zaznaczon¹ opcjê na poprzedni¹.
     */
    void moveUp();

    /**
     * @brief Przesuwa wybór menu w dó³.
     * Funkcja zmienia zaznaczon¹ opcjê na nastepn¹.
     */
    void moveDown();

    /**
     * @brief Zwraca indeks aktualnie zaznaczonej opcji.
     * @return Indeks zaznaczonej opcji.
     */
    int getSelectedIndex() const;
};
