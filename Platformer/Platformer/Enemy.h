#pragma once
#include <SFML/Graphics.hpp>
#include <iostream>
#include <fstream>

/**
 * @brief Klasa reprezentujaca wroga w grze.
 * Zawiera logike dotyczaca ruchu, atakowania, animacji smierci oraz obslugi zdrowia wroga.
 */
class Enemy {
private:

    sf::Clock attackClock; ///< Zegar do obslugi czasu ataku.

    sf::Clock damageClock; ///< Zegar do obslugi czasu otrzymania obrazen.
    float damageInterval;  ///< Czas, po ktorym wróg moze ponownie zadac obrazenia.

    static const float GROUND_Y; ///< Y dla poziomu podlogi.

    float deathAnimationSpeed = 200.f; ///< Predkosc animacji smierci.

    float deathTimer = 0.0f; ///< Licznik czasu animacji smierci.
    sf::Vector2f velocity;   ///< Predkosc ruchu wroga podczas smierci.
    float rotationSpeed = 0.0f; ///< Predkosc obrotu wroga.

protected:
    int attackFrame; ///< Kluczowy numer klatki animacji ataku.
    bool facingRight; ///< Flaga, czy wróg patrzy w prawo.
    unsigned int animationIndex; ///< Indeks aktualnej animacji.
    float speed; ///< Predkosc wroga.
    float direction; ///< Kierunek ruchu wroga.
    float animationTimer; ///< Licznik czasu animacji.
    float animationTimerMax; ///< Maksymalny czas animacji.
    float leftBoundary; ///< Lewa granica obszaru ruchu wroga.
    float rightBoundary; ///< Prawa granica obszaru ruchu wroga.
    bool isDying = false; ///< Flaga smierci wroga.
    bool isAttacking; ///< Flaga ataku wroga.
    sf::Vector2f position; ///< Pozycja wroga.
    sf::Sprite sprite; ///< Sprite reprezentujacy wroga.
    std::vector<sf::Texture> rightTextures; ///< Tekstury dla ruchu wroga w prawo.
    std::vector<sf::Texture> leftTextures; ///< Tekstury dla ruchu wroga w lewo.
    int health; ///< Zdrowie wroga.
    sf::Texture textureRightAttack1; ///< Tekstura ataku wroga w prawo (klatka 1).
    sf::Texture textureRightAttack2; ///< Tekstura ataku wroga w prawo (klatka 2).
    sf::Texture textureLeftAttack1; ///< Tekstura ataku wroga w lewo (klatka 1).
    sf::Texture textureLeftAttack2; ///< Tekstura ataku wroga w lewo (klatka 2).
    void initSprite(); ///< Inicjalizuje sprite'a wroga.

public:
    /**
    * @brief Konstruktor klasy Enemy.
    * Inicjalizuje wroga na podstawie pozycji, predkosci oraz granic ruchu.
    * @param startPosition Poczatkowa pozycja wroga.
    * @param speed Predkosc wroga.
    * @param leftBoundary Lewa granica ruchu wroga.
    * @param rightBoundary Prawa granica ruchu wroga.
    */
    Enemy(sf::Vector2f startPosition, float speed, float leftBoundary, float rightBoundary);

    /**
     * @brief Destruktor klasy Enemy.
     * Zwalnia zasoby przypisane do wroga.
     */
    ~Enemy();


    // Metody

     /**
     * @brief Aktualizuje stan wroga na podstawie uplynulego czasu.
     * @param deltaTime Czas, ktory uplynal od ostatniej aktualizacji.
     */
    virtual void update(float deltaTime);

    /**
     * @brief Renderuje wroga na ekranie.
     * @param window Okno gry, w ktorym rysowany jest wrog.
     */
    virtual void render(sf::RenderWindow& window);

    // Gettery

    /**
     * @brief Zwraca granice wroga.
     * @return Prostokat granicy wroga.
     */
    sf::FloatRect getBounds() const;

    /**
     * @brief Zwraca pozycje wroga.
     * @return Pozycja wroga.
     */
    sf::Vector2f getPosition() const;

    /**
     * @brief Zwraca wektor tekstur dla ruchu wroga w prawo.
     * @return Referencja do wektora tekstur dla ruchu w prawo.
     */
    std::vector<sf::Texture>& getRightTextures() {
        return rightTextures;
    }

    /**
     * @brief Zwraca wektor tekstur dla ruchu wroga w lewo.
     * @return Referencja do wektora tekstur dla ruchu w lewo.
     */
    std::vector<sf::Texture>& getLeftTextures() {
        return leftTextures;
    }


    // Settery

    /**
     * @brief Ustawia nowa pozycje wroga.
     * @param newPosition Nowa pozycja wroga.
     */
    void setPosition(const sf::Vector2f& newPosition);

    /**
     * @brief Ustawia nowy kierunek ruchu wroga.
     * @param newDirection Nowy kierunek ruchu.
     */
    void setDirection(const sf::Vector2f& newDirection);


    /**
     * @brief Ustawia tekstury wroga dla ruchu w prawo i lewo.
     * @param right Wektor tekstur dla ruchu w prawo.
     * @param left Wektor tekstur dla ruchu w lewo.
     */
    void setTextures(const std::vector<sf::Texture>& right, const std::vector<sf::Texture>& left);

    /**
     * @brief Rozpoczyna atak wroga.
     */
    void startAttack();

    /**
     * @brief Aktualizuje stan ataku wroga.
     */
    void updateAttack();

    /**
     * @brief Resetuje stan ataku wroga.
     */
    void resetAttack();

    /**
     * @brief Zwraca, czy wrog aktualnie atakuje.
     * @return Flaga, czy wrog jest w trakcie ataku.
     */
    bool getIsAttacking() const;

    /**
     * @brief Sprawdza, czy wrog moze zadac obrazenia.
     * @return Flaga, czy wrog moze zadac obrazenia.
     */
    bool canDealDamage();

    /**
     * @brief Przemieszcza wroga o okreslony dystans.
     * @param offsetX Dystans, o jaki ma byc przesuniety wrog.
     */
    void move(float offsetX);

    /**
     * @brief Zwraca lewa granice obszaru ruchu wroga.
     * @return Lewa granica ruchu.
     */
    float getLeftBoundary() const;

    /**
     * @brief Zwraca prawa granice obszaru ruchu wroga.
     * @return Prawa granica ruchu.
     */
    float getRightBoundary() const;

    /**
     * @brief Ustawia granice ruchu wroga.
     * @param left Lewa granica ruchu.
     * @param right Prawa granica ruchu.
     */
    void setBoundaries(float left, float right);

    /**
     * @brief Redukuje zdrowie wroga o zadana wartosc.
     * @param damage Wartosc obrazen, ktore wróg otrzymuje.
     */
    void reduceHealth(int damage);
    
    /**
     * @brief Zwraca aktualne zdrowie wroga.
     * @return Aktualne zdrowie wroga.
     */
    int getHealth() const;

    /**
     * @brief Aktualizuje animacje smierci wroga.
     * @param deltaTime Czas, ktory uplynal od ostatniej aktualizacji.
     * @return Zwraca true, jesli animacja smierci jest zakonczona.
     */
    bool updateDeathAnimation(float deltaTime);

    /**
     * @brief Rozpoczyna animacje smierci wroga.
     */
    void startDeathAnimation();

    /**
     * @brief Zwraca, czy wrog jest martwy.
     * @return Flaga, czy wrog jest martwy.
     */
    bool isDead() const;
};