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
     * @brief Inicjalizuje tekstur� dla kreta.
     * Metoda ta ustawia odpowiedni� tekstur� dla obiektu klasy Moles.
     */
    void initTexture();

public:
    /**
     * @brief Konstruktor klasy Moles.
     * Inicjalizuje kreta na podstawie pocz�tkowej pozycji, pr�dko�ci i granic ruchu.
     * @param startPosition Pozycja startowa kreta.
     * @param speed Pr�dko�� poruszania si� kreta.
     * @param leftBoundary Lewa granica ruchu kreta.
     * @param rightBoundary Prawa granica ruchu kreta.
     */
    Moles(sf::Vector2f startPosition, float speed, float leftBoundary, float rightBoundary);

    /**
     * @brief Destruktor klasy Moles.
     * Zwalnia zasoby zwi�zane z obiektem kreta.
     */
    ~Moles();
};