#pragma once
#include "Player.h"

/**
 * @class Background
 * @brief Klasa reprezentuj¹ca t³o gry, które mo¿e poruszaæ siê w zale¿noœci od pozycji gracza.
 */
class Background
{
private:
	sf::Texture textureBackground;
	sf::Sprite backgroundSprite;
	float speed;
	sf::Vector2f position;
	Player* player;


public:
	/**
	 * @brief Konstruktor klasy Background.
	 * @param filname sciezka do pliku z tekstura tla.
	 * @param player Wskaznik na obiekt gracza.
	 */
	Background(const std::string& filname, Player *player);
	
	/**
	* @brief Konstruktor klasy Background.
	* @param filname sciezka do pliku z tekstura tla.
	*/
	Background(const std::string& filname);

	bool isUpdated = false; ///< Flaga okreslajaca, czy tlo zostalo zaktualizowane.
	bool moveLeft = false; ///< Flaga okreslajaca, czy tlo porusza sie w lewo.
	bool moveRight = false; ///< Flaga okreslajaca, czy tlo porusza sie w prawo.

	/**
	 * @brief Aktualizuje pozycje tla na podstawie uplywu czasu i predkosci gracza.
	 * @param deltaTime Czas od ostatniej aktualizacji.
	 * @param characterSpeed Predkosc poruszania sie postaci.
	 */
	void update(float deltaTime, float characterSpeed);
	
	/**
	 * @brief Renderuje tlo w oknie.
	 * @param target Obiekt renderujacy, na ktorym zostanie narysowane tlo.
	 */
	void render(sf::RenderTarget& target);

	/**
	 * @brief Ustawia predkosc poruszania sie tla.
	 * @param newSpeed Nowa predkosc tla.
	 */
	void setSpeed(float newSpeed) {
		speed = newSpeed;
	}

	/**
	 * @brief Pobiera referencje do obiektu sf::Sprite reprezentujacego tlo.
	 * @return Referencja do sprite'a tla.
	 */
	sf::Sprite& getBackgroundSprite();

	/**
	 * @brief Pobiera referencje do obiektu sf::Texture reprezentujacego teksture tla.
	 * @return Referencja do tekstury tla.
	 */
	sf::Texture& getBackgroundTexture();

};

