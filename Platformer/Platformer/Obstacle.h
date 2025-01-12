#pragma once
#include "stdafx.h"
#include "Item.h"

/**
 * @brief Typy przeszkód w grze.
 * Okreslaja rozne typy przeszkod, ktore moga wystêpowac na mapie.
 */
enum class ObstacleType {
	Platform,
	Stone,
	Spikes,
	Scythe,
	Lava,
	FallingStone
};

/**
 * @brief Klasa reprezentujaca przeszkode w grze.
 * Klasa ta dziedziczy po klasie Item i zawiera logike zwiazana z przeszkodami,
 * ktore moga zadawac obrazenia graczowi lub stanowic inne trudnosci.
 */
class Obstacle : public Item
{
private:
	sf::Texture* obstacleTexture;  /**< Tekstura przeszkody. */
	ObstacleType obstacleType;     /**< Typ przeszkody. */
	sf::Vector2f initialPosition;  /**< Poczatkowa pozycja przeszkody. */

	sf::Clock damageClock;         /**< Zegar do kontrolowania interwalu zadawania obrazen. */
	float damageInterval;          /**< Czas pomiedzy zadawaniem obrazen. */

public:
    /**
    * @brief Konstruktor klasy Obstacle.
    * Inicjalizuje przeszkode na podstawie tekstury, pozycji i typu przeszkody.
    * @param obstacleTexture Tekstura przeszkody.
    * @param position Pozycja startowa przeszkody.
    * @param type Typ przeszkody.
    */
    Obstacle(sf::Texture& obstacleTexture, sf::Vector2f position, ObstacleType type);

    /**
     * @brief Zwraca referencje do tekstury przeszkody.
     * @return Referencja do tekstury przeszkody.
     */
    sf::Texture& getTexture() override {
        return *obstacleTexture;
    }

    /**
     * @brief Zwraca typ przeszkody.
     * @return Typ przeszkody.
     */
    ObstacleType getType() const {
        return obstacleType;
    }

    /**
     * @brief Resetuje pozycje przeszkody do poczatkowej.
     * Przywraca przeszkode do pozycji, w ktorej byla na poczatku.
     */
    void resetPosition() {
        this->itemSprite.setPosition(initialPosition);
    }

    /**
     * @brief Ustawia nowa poczatkowa pozycje przeszkody.
     * @param position Nowa poczatkowa pozycja przeszkody.
     */
    void setInitialPosition(const sf::Vector2f& position) {
        initialPosition = position;
    }

    /**
     * @brief Zwraca poczatkowa pozycje przeszkody.
     * @return Pozycja poczatkowa przeszkody.
     */
    sf::Vector2f getInitialPosition() const {
        return initialPosition;
    }

    /**
     * @brief Sprawdza, czy przeszkoda moze zadawac obrazenia.
     * @return true, jesli przeszkoda moze zadawac obrazenia; w przeciwnym razie false.
     */
    bool canDealDamage();
};

