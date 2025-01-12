#pragma once
#include "Bullet.h"
#include "TextureManager.h"
#include "GameState.h"
#include "CollectableItem.h"

struct EquippedItem {
	ItemType type;
	sf::Sprite sprite;
};

/**
 * @brief Klasa reprezentujaca gracza w grze.
 * Klasa ta przechowuje informacje o stanie gracza, takich jak zdrowie,
 * amunicja, umiejetnosci, animacje, oraz obslugiwac rozne akcje, jak strzelanie,
 * poruszanie sie i wykonywanie akcji w grze.
 */
class Player
{
private:
	int health;                         /**< Aktualne zdrowie gracza. */
	float damageCooldown;               /**< Czas do nastepnego mozliwego otrzymania obrazen. */
	int keys = 0;                        /**< Liczba posiadanych kluczy przez gracza. */
	sf::Sprite playerSprite;            /**< Sprite reprezentujacy postac gracza. */
	sf::Sprite playerDeadSprite;        /**< Sprite reprezentujacy martwego gracza. */
	std::vector<sf::Texture> rightTextures; /**< Tekstury dla animacji poruszania sie w prawo. */
	std::vector<sf::Texture> leftTextures;  /**< Tekstury dla animacji poruszania sie w lewo. */
	std::vector<sf::Texture> hpTextures;   /**< Tekstury dla animacji zdrowia gracza. */
	std::vector<sf::Sprite> hpSprite;     /**< Sprite dla animacji zdrowia gracza. */
	std::vector<EquippedItem> equippedItems; /**< Lista przedmiotow, ktore sa wyposazeniem gracza. */

	int currentAmmo = 15;               /**< Ilosc aktualnej amunicji. */
	sf::Text ammoText;                  /**< Tekst wyswietlajacy liczbe amunicji. */
	sf::Font font;                      /**< Czcionka do wyswietlania tekstow. */
	sf::Texture amuTexture;             /**< Tekstura dla amunicji. */
	sf::Sprite amuSprite;               /**< Sprite reprezentujacy amunicje. */

	TextureManager textureManager;      /**< Menedzer tekstur. */

	// Grawitacja
	float GRAVITY = 980.f;              /**< Sila grawitacji. */
	float JUMP_STRENGTH = -550.f;       /**< Sila skoku. */
	float verticalVelocity = 0.0f;      /**< Aktualna predkosc pionowa gracza. */

	GameState gameState;                /**< Stan gry, w jakim znajduje sie gracz. */
	std::vector<Bullet> bullets;        /**< Lista wystrzelonych kul. */
	sf::Texture bulletTexture;          /**< Tekstura dla kuli. */
	float bulletDir;                    /**< Kierunek strzalu. */

	// Zegar animacji
	float animationTimer;               /**< Czas do zmiany animacji. */
	float animationTimerMax;            /**< Maksymalny czas jednej klatki animacji. */
	unsigned int animationIndex;        /**< Indeks bieżącej animacji. */

	// Pozycja poczatkowa postaci
	sf::Vector2f playerPosition;        /**< Pozycja gracza na ekranie. */
	float characterSpeed;               /**< Predkosc poruszania gracza. */

	// Zmienne stanu
	bool isJumping = false;             /**< Flaga informujaca, czy gracz skacze. */
	bool isOnGround = false;            /**< Flaga informujaca, czy gracz jest na ziemi. */
	bool canMoveRight = true;           /**< Flaga informujaca, czy gracz moze sie poruszac w prawo. */
	bool canMoveLeft = true;            /**< Flaga informujaca, czy gracz moze sie poruszac w lewo. */
	bool isDead = false;                /**< Flaga informujaca, czy gracz jest martwy. */
	bool isFalling = false;             /**< Flaga informujaca, czy gracz opada. */
	bool fallen = false;                /**< Flaga informujaca, czy gracz upadl. */
	bool isDeadSpriteSet = false;       /**< Flaga informujaca, czy sprite martwego gracza jest ustawiony. */
	bool movingWithEqRight = false;     /**< Flaga informujaca, czy gracz porusza sie z ekwipunkiem w prawo. */
	bool movingWithEqLeft = false;      /**< Flaga informujaca, czy gracz porusza sie z ekwipunkiem w lewo. */
	bool wearingWings = false;          /**< Flaga informujaca, czy gracz nosi skrzydla. */
	bool wearingHat = false;            /**< Flaga informujaca, czy gracz nosi kapelusz. */
	bool wearingHelmet = false;         /**< Flaga informujaca, czy gracz nosi helm. */

	void initText();                    /**< Inicjalizuje teksty do wyswietlania w grze. */
	void initSprite();                  /**< Inicjalizuje sprite'y gracza. */
	void initTexture();                 /**< Inicjalizuje tekstury dla gracza. */

	// Strzaly
	float shootCooldown;                /**< Czas od ostatniego strzalu. */
	float shootCooldownMax;             /**< Maksymalny czas na strzal. */
	int experience;                     /**< Ilosc zdobytego doswiadczenia. */
	int level;                          /**< Poziom gracza. */
	int experienceToNext;               /**< Ilosc doswiadczenia potrzebna do nastepnego poziomu. */
	int maxHealth;                      /**< Maksymalne zdrowie gracza. */
	int damage;                         /**< Sila ataku gracza. */
	bool levelUpMenuActive = false;     /**< Flaga informujaca, czy menu awansu jest aktywne. */


public:
	/**
	  * @brief Konstruktor klasy Player.
	  * Inicjalizuje postac gracza z ustawionymi parametrami.
	  * @param playerPosition Pozycja gracza na ekranie.
	  * @param hp Poczatkowe zdrowie gracza.
	  */
	Player(sf::Vector2f playerPosition, int hp);

	/**
	 * @brief Destruktor klasy Player.
	 * Zwalnia zasoby związane z obiektem gracza.
	 */
	~Player();

	//Metoda zwracajaca biezaca pozycje postaci
	sf::Vector2f getPlayerPosition() {
		return this->playerSprite.getPosition();
	}

	sf::Sprite getPlayerSprite() {
		return playerSprite;
	}

	float getCharacterSpeed() {
		return characterSpeed;
	}

	sf::FloatRect getPlayerBounds() {
		return playerSprite.getGlobalBounds();
	}

	/**
	 * @brief Zmniejsza zdrowie gracza.
	 * Funkcja redukuje zdrowie gracza o zadaną ilość. Jeżeli zdrowie gracza spadnie poniżej 0, postać umiera.
	 * @param amount Ilość zdrowia, którą należy odjąć od obecnego stanu zdrowia gracza.
	 */
	void reduceHealth(int amount);

	/**
	 * @brief Aktualizuje animacje gracza.
	 * Funkcja odpowiada za aktualizacje animacji gracza w zaleznosci od uplywu czasu.
	 * @param deltaTime Czas, który uplynal od ostatniej klatki, uzywany do synchronizacji animacji.
	 */
	void updateAnimations(float deltaTime);

	/**
	 * @brief Wykonuje strzal.
	 * Funkcja odpowiada za strzaly gracza. Jezeli czas oczekiwania na kolejny strzal minal, strzal zostaje wystrzelony.
	 */
	void shoot();

	/**
	 * @brief Dodaje grawitacje do gracza.
	 * Funkcja aktualizuje predkosc pionowa gracza, aby postac spadala w kierunku ziemi.
	 * @param deltaTime Czas, ktory uplynal od ostatniej klatki, uzywany do symulacji grawitacji.
	 */
	void gravitation(float deltaTime);

	/**
	 * @brief Zatrzymuje gracza na krawedziach ekranu.
	 * Funkcja odpowiada za ograniczenie ruchu gracza do wnetrza ekranu, tak aby nie mogl on wyjsc poza jego granice.
	 */
	void holdPlayerAtEdges();

	/**
	 * @brief Ustawia, czy gracz jest na ziemi.
	 * Funkcja ustawia status gracza, czy znajduje sie na ziemi, co wplywa na mozliwosc skakania.
	 * @param isOnGround Flaga wskazujaca, czy gracz jest na ziemi.
	 */
	void setOnGround(bool isOnGround);

	/**
	 * @brief Ustawia pionowa predkosc gracza.
	 * Funkcja ustawia predkosc ruchu gracza w osi Y, co wplywa na grawitacje i skakanie.
	 * @param verticalVelocity Wartosc predkosci pionowej.
	 */
	void setVerticalVelocity(float verticalVelocity);

	/**
	 * @brief Aktualizuje ruch gracza.
	 * Funkcja odpowiada za aktualizacje pozycji gracza na podstawie wcisnietych klawiszy, grawitacji, itp.
	 * @param deltaTime Czas, ktory uplynal od ostatniej klatki, uzywany do synchronizacji ruchu.
	 * @param event Wydarzenie reprezentujace wejscie od gracza, ktore zmienia ruch postaci.
	 */
	void update(float deltaTime,sf::Event &event);

	/**
	 * @brief Renderuje gracza na ekranie.
	 * Funkcja rysuje gracza na ekranie w danym miejscu, korzystajac z aktualnej tekstury.
	 * @param target Cel renderowania.
	 */
	void render(sf::RenderTarget& target);

	/**
	 * @brief Ustawia status skakania gracza.
	 * Funkcja ustawia, czy gracz jest w trakcie skoku.
	 * @param jumping Flaga wskazujaca, czy gracz jest w trakcie skoku.
	 */
	void setIsJumping(bool jumping);

	/**
	 * @brief Zwraca pionowa predkosc gracza.
	 * Funkcja zwraca aktualna predkosc gracza w osi Y, co jest pomocne przy obliczeniach zwiazanych z grawitacja.
	 * @return Aktualna pionowa predkosc gracza.
	 */
	float getVerticalVelocity() const;

	/**
	 * @brief Zwraca liste pociskow wystrzelonych przez gracza.
	 * Funkcja zwraca wektor pociskow, które sa aktualnie w grze, wystrzelonych przez gracza.
	 * @return Lista pociskow gracza.
	 */
	std::vector<Bullet>& getBullets();

	/**
	 * @brief Umozliwia ruch w prawo.
	 * Funkcja ustawia, czy gracz moze poruszac sie w prawo.
	 * @param canMove Flaga wskazujaca, czy gracz moze poruszac sie w prawo.
	 */
	void setCanMoveRight(bool canMove) {
		this->canMoveRight = canMove;
	}

	/**
	 * @brief Umozliwia ruch w lewo.
	 * Funkcja ustawia, czy gracz moze poruszac sie w lewo.
	 * @param canMove Flaga wskazujaca, czy gracz moze poruszac sie w lewo.
	 */
	void setCanMoveLeft(bool canMove) {
		this->canMoveLeft = canMove;
	}

	/**
	 * @brief Ustawia pozycje gracza.
	 * Funkcja ustawia pozycje gracza w przestrzeni gry.
	 * @param posx Nowa pozycja gracza w osi X.
	 * @param posy Nowa pozycja gracza w osi Y.
	 */
	void setPlayerPosition(float posx, float posy) {
		this->playerSprite.setPosition(posx, posy);
	}

	/**
	 * @brief Ustawia, czy gracz jest martwy.
	 * Funkcja ustawia status gracza jako martwego, co wplywa na jego dalsze interakcje w grze.
	 * @param isDead Flaga wskazujaca, czy gracz jest martwy.
	 */
	void setIsDead(bool isDead) {
		this->isDead = isDead;
	}

	/**
	 * @brief Ustawia, czy gracz upadl.
	 * Funkcja ustawia status gracza jako upadlego, co jest istotne dla mechaniki gry.
	 * @param fallen Flaga wskazujaca, czy gracz upadl.
	 */
	void setFallen(bool fallen) {
		this->fallen = fallen;
	}

	/**
	 * @brief Ustawia liczbe kluczy posiadanych przez gracza.
	 * Funkcja ustawia liczbe kluczy, które gracz posiada w danej chwili.
	 * @param keys Nowa liczba kluczy posiadanych przez gracza.
	 */
	void setKeys(int keys) {
		this->keys = keys;
	}

	/**
	 * @brief Ustawia liczbe amunicji gracza.
	 * Funkcja ustawia liczbe amunicji gracza, co wplywa na dostepnosc strzalów.
	 * @param amo Liczba amunicji gracza.
	 */
	void setCurrentAmo(int amo) {
		this->currentAmmo = amo;
	}

	/**
	 * @brief Ustawia zdrowie gracza.
	 * Funkcja ustawia zdrowie gracza na nowa wartosc i aktualizuje odpowiednie wyswietlanie tego zdrowia.
	 * @param health Nowa wartosc zdrowia gracza.
	 */
	void setHealth(int health) {
		hpSprite.clear();
		this->health = health;
	}

	/**
	 * @brief Aktualizuje wektor zdrowia gracza.
	 * Funkcja odpowiedzialna za zaktualizowanie wektora, który przechowuje reprezentacje graficzne zdrowia gracza.
	 */
	void updateHealthVector();

	/**
	 * @brief Zwieksza liczbe amunicji.
	 * Funkcja zwieksza liczbe amunicji gracza o 1.
	 */
	void incrementCurrentAmo();

	/**
	 * @brief Aktualizuje tekst wyswietlajacy liczbe amunicji.
	 * @param currentAmmo Nowa wartosc liczby amunicji.
	 */
	void updateAmmoText(int currentAmmo);

	/**
	 * @brief Aktualizuje zdrowie gracza.
	 * @param count Liczba punktów zdrowia, które maja zostac dodane do gracza.
	 */
	void updateHealth(int count = 1);

	/**
	 * @brief Zwraca status skakania gracza.
	 * Funkcja zwraca, czy gracz jest w trakcie skoku.
	 * @return Flaga wskazujaca, czy gracz jest w trakcie skoku.
	 */
	bool getIsJumping() const;

	/**
	 * @brief Zwraca aktualna liczbe amunicji.
	 * @return Liczba amunicji.
	 */
	int getCurrentAmo();

	/**
	 * @brief Zwraca aktualne zdrowie gracza.
	 * @return Aktualne zdrowie gracza.
	 */
	int getCurrentHealth() const;

	/**
	 * @brief Zwraca status martwego gracza.
	 * @return Flaga wskazujaca, czy gracz jest martwy.
	 */
	bool getIsDead() {
		return isDead;
	}

	/**
	 * @brief Zwraca liczbe kluczy gracza.
	 * @return Liczba kluczy gracza.
	 */
	int getKeys() {
		return keys;
	}

	/**
	 * @brief Zwraca status upadlego gracza.
	 * @return Flaga wskazujaca, czy gracz upadl.
	 */
	bool getIsFallen() {
		return fallen;
	}

	/**
	 * @brief Zwraca, czy gracz nosi helm.
	 * @return Flaga wskazujaca, czy gracz nosi helm.
	 */
	bool getWearingHelmet() {
		return wearingHelmet;
	}

	/**
	 * @brief Sprawdza, czy gracz moze otrzymac obrazenia.
	 * Funkcja sprawdza, czy gracz moze otrzymac obrazenia, zaleznie od cooldownu.
	 * @return Flaga wskazujaca, czy gracz moze otrzymac obrazenia.
	 */
	bool canTakeDamage() const {
		return damageCooldown <= 0;
	}

	/**
	* @brief Ustawia teksture dla elementu ekwipunku.
	* Funkcja ustawia teksture dla wybranego elementu ekwipunku gracza.
	* @param filepath Sciezka do pliku tekstury.
	* @param name Nazwa elementu.
	* @param itemType Typ elementu ekwipunku.
	*/
	void setEqTexture(const std::string& filepath, const std::string& name, ItemType itemType);
	/**
	 * @brief Usuwa element ekwipunku.
	 * Funkcja usuwa dany element ekwipunku gracza.
	 * @param itemType Typ elementu ekwipunku do usuniecia.
	 */
	void removeEquippedItem(ItemType itemType);

	/**
	 * @brief Zwraca liste wyposazonych przedmiotow.
	 * Funkcja zwraca liste przedmiotów, które gracz ma obecnie w ekwipunku.
	 * @return Wektor przedmiotów ekwipunku.
	 */
	std::vector<EquippedItem> getEquippedItems() const {
		return equippedItems;
	}

	/**
	 * @brief Aktualizuje pozycje przedmiotów ekwipunku.
	 * Funkcja odpowiada za aktualizacje pozycji elementów ekwipunku gracza na ekranie.
	 */
	void updateEqPosition();

	/**
	 * @brief Ustawia, czy gracz nosi skrzydla.
	 * @param wearing Flaga wskazujaca, czy gracz nosi skrzydla.
	 */
	void setWearingWings(bool wearing) {
		wearingWings = wearing;
	}

	/**
	 * @brief Ustawia, czy gracz nosi kapelusz.
	 * @param wearing Flaga wskazujaca, czy gracz nosi kapelusz.
	 */
	void setWearingHat(bool wearing) {
		wearingHat = wearing;
	}

	/**
	 * @brief Ustawia, czy gracz nosi helm.
	 * @param wearing Flaga wskazujaca, czy gracz nosi helm.
	 */
	void setWearingHelmet(bool wearing) {
		wearingHelmet = wearing;
	}

	/**
	 * @brief Dodaje doswiadczenie gracza.
	 * Funkcja zwieksza ilosc doswiadczenia gracza.
	 * @param experience Ilosc doswiadczenia, które ma zostac dodane do gracza.
	 */
	void addExperience(int amount);

	/**
	 * @brief Sprawdza, czy gracz może awansowac na wyzszy poziom.
	 * Funkcja sprawdza, czy gracz osiągnal wymagany prog doswiadczenia do awansu na wyzszy poziom.
	 * @return Flaga wskazujaca, czy gracz moze awansowac na wyzszy poziom.
	 */
	bool checkLevelUp();

	/**
	 * @brief Zwraca poziom gracza.
	 * Funkcja zwraca aktualny poziom gracza w grze.
	 * @return Poziom gracza.
	 */
	int getLevel() const;

	/**
	 * @brief Zwraca doswiadczenie gracza.
	 * Funkcja zwraca ilosc doswiadczenia posiadana przez gracza.
	 * @return Doswiadczenie gracza.
	 */
	int getExperience() const;

	/**
	 * @brief Zwraca doswiadczenie potrzebne do następnego poziomu.
	 * Funkcja zwraca ilosc doswiadczenia, ktore gracz musi zdobyc, aby awansowac na nastepny poziom.
	 * @return Doswiadczenie potrzebne do nastepnego poziomu.
	 */
	int getExperienceToNext() const;

	/**
	 * @brief Zwraca maksymalne zdrowie gracza.
	 * Funkcja zwraca maksymalna ilosc zdrowia gracza, ktore moze posiadac.
	 * @return Maksymalne zdrowie gracza.
	 */
	int getMaxHealth() const;

	/**
	 * @brief Zwraca obrazenia gracza.
	 * Funkcja zwraca wartosc obrazen, ktore gracz zadaje w grze.
	 * @return Obrazenia gracza.
	 */
	int getDamage() const;

	/**
	 * @brief Zwieksza maksymalne zdrowie gracza.
	 * Funkcja zwieksza maksymalne zdrowie gracza o okreslona wartosc.
	 */
	void increaseMaxHealth();

	/**
	 * @brief Zwieksza obrazenia gracza.
	 * Funkcja zwieksza obrazenia zadawane przez gracza w grze.
	 */
	void increaseDamage();

	/**
	 * @brief Zwieksza predkosc gracza.
	 * Funkcja zwieksza predkosc poruszania sie gracza w grze.
	 */
	void increaseSpeed();

	/**
	 * @brief Czysci ekwipunek gracza.
	 * Funkcja usuwa wszystkie przedmioty z ekwipunku gracza.
	 */
	void clearEq();
};

	