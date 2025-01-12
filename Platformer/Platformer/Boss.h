#pragma once
#include "Enemy.h"
#include "Bullet.h"
#include <random>

/**
 * @brief Klasa reprezentujaca bossa w grze.
 * Boss ma zdolnosc skakania, strzelania oraz atakowania graczem.
 */
class Boss :
    public Enemy
{
private:
    /**
       * @brief Inicjalizuje teksture bossa.
       */
    void initTexture();

    /**
     * @brief Aktualizuje stan bossa.
     * Zawiera logike skakania i strzelania.
     * @param deltaTime Zmienna czasu od ostatniej aktualizacji.
     */
    void update(float deltaTime) override;

    /**
     * @brief Renderuje bossa na ekranie.
     * @param window Okno renderowania.
     */
    void render(sf::RenderWindow& window) override;

    float jumpTimer; /**< Zegar dla skakania */
    bool isJumping; /**< Flaga okreslajaca, czy boss skacze */
    float jumpTime; /**< Czas skoku */
    float jumpDuration; /**< Czas trwania skoku */

    sf::Texture bulletTexture; /**< Tekstura pociskow bossa */
    std::vector<Bullet> bullets; /**< Wektor pociskow bossa */
    float shootTimer = 0.0f; /**< Zegar dla strzelania */
    float shootInterval = 1.0f; /**< Interwal czasowy pomiedzy strzalami */
    float bulletSpeed = 300.0f; /**< Predkosc pociskow */

public:
    /**
     * @brief Konstruktor bossa.
     * @param startPosition Poczatkowa pozycja bossa.
     * @param speed Szybkosci poruszania sie bossa.
     * @param leftBoundary Lewa granica obszaru poruszania sie bossa.
     * @param rightBoundary Prawa granica obszaru poruszania sie bossa.
     */
    Boss(sf::Vector2f startPosition, float speed, float leftBoundary, float rightBoundary);

    /**
     * @brief Destruktor bossa.
     */
    ~Boss();

    /**
     * @brief Zwraca wektor pociskow bossa.
     * @return Wektor pociskow.
     */
    std::vector<Bullet>& getBullets();
};

