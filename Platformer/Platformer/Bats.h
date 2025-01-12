#pragma once
#include "Enemy.h"
#include <cmath>

/**
 * @brief Klasa reprezentujaca nietoperze w grze.
 * Nietoperze poruszaja sie z okreslonym katem obrotu i predkoscia obrotu.
 */
class Bats :
    public Enemy
{
private:
    void initTexture(); /**< Inicjalizacja tekstury nietoperza */
    float rotationAngle; /**< Kat obrotu nietoperza */
    float rotationBatSpeed; /**< Predkosc obrotu nietoperza */

    /**
     * @brief Aktualizuje pozycje nietoperza.
     * Uwzglednia kat obrotu i predkosc obrotu.
     * @param deltaTime Zmienna czasu od ostatniej aktualizacji.
     */
    void update(float deltaTime) override;

public:
    /**
     * @brief Konstruktor nietoperza.
     * @param startPosition Poczatkowa pozycja nietoperza.
     * @param speed Szybkosci poruszania sie nietoperza.
     * @param leftBoundary Lewa granica obszaru poruszania sie nietoperza.
     * @param rightBoundary Prawa granica obszaru poruszania sie nietoperza.
     */
    Bats(sf::Vector2f startPosition, float speed, float leftBoundary, float rightBoundary);

    /**
     * @brief Destruktor nietoperza.
     */
    ~Bats();
};
