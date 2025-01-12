#pragma once
/**
 * @brief Klasa reprezentujaca pocisk w grze.
 * Pocisk moze poruszac sie w okreslonym kierunku z okreslona predkoscia i mozna sprawdzic, czy jest poza ekranem.
 */
class Bullet
{
private:
	sf::Sprite bulletSprite;      ///< Sprite reprezentujacy pocisk.
	sf::Vector2f startPos;        ///< Poczatkowa pozycja pocisku.
	sf::Vector2f direction;       ///< Kierunek, w ktorym porusza sie pocisk.
	sf::Vector2f velocity;        ///< Predkosc pocisku.
	float bulletSpeed;            ///< Predkosc pocisku.


public:
	/**
	 * @brief Konstruktor klasy Bullet.
	 * Inicjalizuje pocisk z tekstura, pozycja startowa, kierunkiem oraz predkoscia.
	 * @param texture Tekstura pocisku.
	 * @param startPos Poczatkowa pozycja pocisku.
	 * @param direction Kierunek, w ktorym pocisk ma podazac.
	 * @param bulletSpeed Predkosc pocisku.
	 */
	Bullet(sf::Texture& texture, sf::Vector2f startPos, sf::Vector2f direction, float bulletSpeed);
	/**
	  * @brief Destruktor klasy Bullet.
	  * Usuwa zasoby przypisane do pocisku.
	  */
	~Bullet();

	/**
	 * @brief Sprawdza, czy pocisk znajduje sie poza ekranem.
	 * Uzywane do usuniecia pocisku z listy.
	 * @return Zwraca true, jesli pocisk jest poza ekranem.
	 */
	bool isOffScreen();

	/**
	 * @brief Zwraca aktualna pozycje pocisku.
	 * @return Pozycja pocisku w postaci wektora.
	 */
	sf::Vector2f getBulletPosition();

	/**
	 * @brief Zwraca referencje do sprite'a pocisku.
	 * @return Referencja do obiektu sf::Sprite.
	 */
	sf::Sprite& getBulletSprite();

	/**
	 * @brief Aktualizuje stan pocisku na podstawie uplynulego czasu.
	 * @param deltaTime Czas, ktory uplynal od ostatniej aktualizacji.
	 */
	void update(float deltaTime);

	/**
	* @brief Renderuje pocisk na ekranie.
	* @param target Cel renderowania, zazwyczaj okno gry.
	*/
	void render(sf::RenderTarget* target) const;

	/**
	* @brief Zwraca prostokat granic textury pocisku.
	* @return Prostokat granic textury pocisku.
	*/
	sf::FloatRect getBounds() const;

};


