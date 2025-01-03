#pragma once
#include <SFML/Graphics.hpp>
#include <vector>

class StatsMenu {
private:
    std::vector<sf::Text> options; // Opcje menu
    int selectedIndex;             // Aktualnie wybrana opcja
    sf::Font font;                 // Czcionka u�ywana w menu

public:
    explicit StatsMenu(const sf::Font& font); // Konstruktor
    void draw(sf::RenderWindow& window); // Rysowanie menu
    void moveUp();                      // Przesuni�cie w g�r�
    void moveDown();                    // Przesuni�cie w d�
    int getSelectedIndex() const;       // Pobranie indeksu zaznaczonej opcji
};
