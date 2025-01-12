#pragma once
#include "Enemy.h"

/**
 * @brief Klasa reprezentujaca wroga - kret.
 * Dziedziczy po klasie Enemy, implementujac specyficzne dla kreta zachowanie.
 */
class Moles : public Enemy
{
private:
    /**
     * @brief Inicjalizuje teksturê dla kreta.
     * Metoda ta ustawia odpowiedni¹ teksturê dla obiektu klasy Moles.
     */
    void initTexture();

public:
    /**
     * @brief Konstruktor klasy Moles.
     * Inicjalizuje kreta na podstawie pocz¹tkowej pozycji, prêdkoœci i granic ruchu.
     * @param startPosition Pozycja startowa kreta.
     * @param speed Prêdkoœæ poruszania siê kreta.
     * @param leftBoundary Lewa granica ruchu kreta.
     * @param rightBoundary Prawa granica ruchu kreta.
     */
    Moles(sf::Vector2f startPosition, float speed, float leftBoundary, float rightBoundary);

    /**
     * @brief Destruktor klasy Moles.
     * Zwalnia zasoby zwi¹zane z obiektem kreta.
     */
    ~Moles();
};