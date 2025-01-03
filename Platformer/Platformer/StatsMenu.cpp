#include "stdafx.h"
#include "StatsMenu.h"

// Konstruktor
StatsMenu::StatsMenu(const sf::Font& font) : font(font), selectedIndex(0) {
    // Nazwy opcji
    std::vector<std::string> statNames = { "Increase Max Health +1", "Increase Damage +1", "Increase Speed +50" };

    // Tworzenie tekstów dla ka¿dej opcji menu
    for (size_t i = 0; i < statNames.size(); ++i) {
        sf::Text text;
        text.setFont(this->font);
        text.setString(statNames[i]);
        text.setCharacterSize(30);
        text.setFillColor(i == 0 ? sf::Color::Red : sf::Color::White); // Zaznaczenie pierwszej opcji
        text.setPosition(100.f, 100.f + i * 50.f); // Pozycje opcji w pionie
        options.push_back(text);
    }
}

// Rysowanie menu
void StatsMenu::draw(sf::RenderWindow& window) {
    for (const auto& option : options) {
        window.draw(option);
    }
}

// Przesuniêcie zaznaczenia w górê
void StatsMenu::moveUp() {
    if (selectedIndex > 0) {
        options[selectedIndex].setFillColor(sf::Color::White); // Odznacz aktualn¹ opcjê
        --selectedIndex;
        options[selectedIndex].setFillColor(sf::Color::Red);   // Zaznacz now¹ opcjê
    }
}

// Przesuniêcie zaznaczenia w dó³
void StatsMenu::moveDown() {
    if (selectedIndex < options.size() - 1) {
        options[selectedIndex].setFillColor(sf::Color::White); // Odznacz aktualn¹ opcjê
        ++selectedIndex;
        options[selectedIndex].setFillColor(sf::Color::Red);   // Zaznacz now¹ opcjê
    }
}

// Pobranie indeksu wybranej opcji
int StatsMenu::getSelectedIndex() const {
    return selectedIndex;
}
