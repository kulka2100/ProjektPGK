#pragma once
#include "Enemy.h"

/**
 * @brief Klasa reprezentujaca kota w grze.
 * Kot jest typem wroga, ktory porusza sie po ekranie.
 */
class Cats :
    public Enemy
{
private:
    /**
     * @brief Inicjalizuje teksture kota.
     */
    void initTexture();

public:
    /**
     * @brief Konstruktor kota.
     * @param startPosition Poczatkowa pozycja kota.
     * @param speed Szybkosci poruszania sie kota.
     * @param leftBoundary Lewa granica obszaru poruszania sie kota.
     * @param rightBoundary Prawa granica obszaru poruszania sie kota.
     */
    Cats(sf::Vector2f startPosition, float speed, float leftBoundary, float rightBoundary);

    /**
     * @brief Destruktor kota.
     */
    ~Cats();
};

