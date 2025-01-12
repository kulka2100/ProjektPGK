#pragma once
#include "stdafx.h"

/**
 * @brief Klasa bazowa reprezentujaca przedmiot w grze.
 * Klasa ta zawiera podstawowe funkcje dla przedmiotow, takie jak renderowanie, ruch i obliczanie granic.
 */
class Item
{
protected:
	sf::Sprite itemSprite;  ///< Sprite reprezentujacy przedmiot w grze.
public:
    /**
     * @brief Zwraca granice (bounding box) przedmiotu.
     * @return sf::FloatRect Granice przedmiotu.
     */
    virtual sf::FloatRect getBounds() {
        return itemSprite.getGlobalBounds();
    }

    /**
     * @brief Zwraca pozycje przedmiotu na ekranie.
     * @return sf::Vector2f Pozycja przedmiotu.
     */
    virtual sf::Vector2f getPosition() {
        return itemSprite.getPosition();
    }

    /**
     * @brief Aktualizuje pozycje przedmiotu.
     * @param pos Nowa pozycja, o ktora ma byc przesuniety przedmiot.
     */
    virtual void update(sf::Vector2f pos) {
        itemSprite.move(pos); // Bazowa logika ruchu
    }

    /**
     * @brief Renderuje przedmiot na ekranie.
     * @param window Okno gry, w ktorym przedmiot jest renderowany.
     */
    virtual void render(sf::RenderWindow& window) {
        window.draw(itemSprite); // Bazowa logika renderowania
    }

    /**
     * @brief Zwraca referencje do sprite'a przedmiotu.
     * @return sf::Sprite& Referencja do sprite'a przedmiotu.
     */
    virtual sf::Sprite& getSprite() {
        return itemSprite;
    }

    /**
     * @brief Czysta funkcja wirtualna do pobrania tekstury przedmiotu.
     * Funkcja musi byc zaimplementowana w klasach dziedziczacych.
     * @return sf::Texture& Tekstura przedmiotu.
     */
    virtual sf::Texture& getTexture() = 0; // To wymaga implementacji w klasach pochodnych

    /**
     * @brief Destruktor klasy Item.
     * Destruktor nie wykonuje specjalnych operacji, ale jest wymagany w klasie bazowej.
     */
    virtual ~Item() = default;
};

