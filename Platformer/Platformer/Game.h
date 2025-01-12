#pragma once
#include "Player.h"
#include "Background.h"
#include "Menu.h"
#include "Maps.h"
#include "Obstacle.h"
#include "TextureManager.h"
#include "Enemy.h"
#include "GameState.h"
#include "CollectableItem.h"
#include "Moles.h"
#include "MapInitializer.h"
#include "Cats.h"
#include "Bats.h"
#include "Settings.h"
#include "Boss.h"
#include "Pause.h"
#include "Equipment.h"
#include "StatsMenu.h"
#include <fstream>


/**
 * @brief Klasa reprezentujaca glowna logike gry.
 * Zawiera wszystkie elementy rozgrywki, takie jak gracz, tlo, wrogowie, przeszkody, przedmioty itp.
 */
class Game
{
private:
    int width;                          ///< Szerokosc okna gry.
    int height;                         ///< Wysokosc okna gry.
    sf::Event event;                    ///< Wydarzenie zwiazane z oknem gry.
    sf::RenderWindow window;            ///< Okno gry.
    sf::Clock clock;                    ///< Zegar gry.
    std::vector<Enemy*> enemies;        ///< Lista wrogow.
    float deltaTime;                    ///< Czas, jaki uplyn像 od ostatniej klatki.
    sf::Font font;                      ///< Czcionka do rysowania tekstu.
    StatsMenu* statsMenu;               ///< Menu statystyk gry.

    Player* player;                     ///< Gracz.
    Background* background;             ///< Tlo.
    Menu* menu;                         ///< Menu.
    Maps* maps;                         ///< Mapy.
    Settings* settings;                 ///< Ustawienia.
    Pause* pause;                       ///< Pauza.
    Equipment* eq;                      ///< Ekwipunek.
    MapInitializer* mapInitializer;     ///< Inicjalizator map.
    TextureManager textureManager;      ///< Menedzer tekstur.
    std::vector<Obstacle> obstacles;    ///< Lista przeszkod.
    std::vector<CollectableItem> collectableItems; ///< Lista przedmiotow do zebrania.
    std::vector<CollectableItem> carrotOnTree; ///< Lista marchewek na drzewach.
    std::vector<bool> unlockedMaps = { true, false, false, false, false }; ///< Lista map, z kt鏎ych tylko pierwsza jest odblokowana.
    bool isMenuActive;                  ///< Flaga aktywacji menu.
    bool isPlayed;                      ///< Flaga informujaca, czy gra byla rozegrana.
    GameState gameState;                ///< Stan gry.
    int currentMap = 0;                 ///< Aktualnie wybrana mapa.
    int difficultyLvel = 0;             ///< Poziom trudnosci.
    int selectedEq = 0;                 ///< Wybrany przedmiot w ekwipunku.

    bool moveLeftObstacle = true;       ///< Flaga kierunku ruchu przeszkody w lewo.
    bool moveRightObstacle = false;     ///< Flaga kierunku ruchu przeszkody w prawo.
    bool isGameLoaded = false;          ///< Flaga informujaca, czy gra zostala zaladowana.

    /**
     * @brief Inicjalizuje okno gry.
     */
    void initWindow();

    /**
     * @brief Inicjalizuje gracza.
     */
    void initPlayer();

    /**
     * @brief Inicjalizuje tlo na podstawie indeksu mapy.
     * @param mapIndex Indeks mapy.
     */
    void initBackground(int mapIndex);

    /**
     * @brief Inicjalizuje przeszkody na podstawie indeksu mapy.
     * @param mapIndex Indeks mapy.
     */
    void initObstacles(int mapIndex);

    /**
     * @brief Inicjalizuje przedmioty do zebrania na podstawie indeksu mapy.
     * @param mapIndex Indeks mapy.
     */
    void initCollectableItems(int mapIndex);

    /**
     * @brief Inicjalizuje wrogow.
     */
    void initEnemies(int mapIndex);

    /**
     * @brief Aktualizuje stan wrogow.
     * @param deltaTime Czas, jaki uplyn像 od ostatniej klatki.
     */
    void updateEnemies(float deltaTime);

    /**
     * @brief Renderuje wrogow.
     */
    void renderEnemies();

    /**
     * @brief Sprawdza kolizje pomiedzy graczem a wrogami.
     */
    void checkPlayerEnemyCollision();

    /**
     * @brief Sprawdza kolizje pomiedzy pociskami a wrogami.
     */
    void checkBulletEnemyCollision();

    /**
     * @brief Sprawdza kolizje pomiedzy pociskami a graczem.
     */
    void checkBulletPlayerCollision();

    /**
     * @brief Sprawdza stan panelu ekwipunku.
     */
    void checkEqPanel();


public:
    /**
     * @brief Konstruktor klasy Game.
     * Inicjalizuje wszystkie elementy gry.
     * @param width Szerokosc okna gry.
     * @param height Wysokosc okna gry.
     */
	Game(int width, int height);

    /**
     * @brief Destruktor klasy Game.
     * Zwolnia zasoby wykorzystywane przez obiekty gry.
     */
	~Game();

    /**
     * @brief Zwraca okno gry.
     * @return Referencja do okna gry.
     */
	sf::RenderWindow& getWindow();

    /**
     * @brief Zwraca szerokosc okna gry.
     * @return Szerokosc okna gry.
     */
	int getWidth() {
		return width;
	}
  
    /**
     * @brief Zwraca wysokosc okna gry.
     * @return Wysokosc okna gry.
     */
	int getHeight() {
		return height;
	}

    /**
    * @brief Aktualizuje stan gracza.
    * @param deltaTime Czas, jaki uplyn像 od ostatniej klatki.
    */
    void updatePlayer(float deltaTime);

    /**
     * @brief Renderuje gracza na ekranie.
     */
    void renderPlayer();

    /**
     * @brief Aktualizuje stan przedmiotow do zebrania.
     * @param deltaTime Czas, jaki uplyn像 od ostatniej klatki.
     */
    void updateCollectableItems(float deltaTime);

    /**
     * @brief Renderuje przedmioty do zebrania na ekranie.
     */
    void renderCollectableItems();

    /**
     * @brief Aktualizuje przeszkody na ekranie.
     * @param deltaTime Czas, jaki uplyn像 od ostatniej klatki.
     */
    void updateObstacles(float deltaTime);

    /**
     * @brief Renderuje przeszkody na ekranie.
     */
    void renderObstacles();

    /**
     * @brief Aktualizuje tlo gry.
     * @param deltaTime Czas, jaki uplyn像 od ostatniej klatki.
     * @param characterSpeed Predkosc poruszania sie gracza.
     */
    void updateBackground(float deltaTime, float characterSpeed);

    /**
     * @brief Renderuje tlo na ekranie.
     */
    void renderBackground();

    /**
     * @brief G堯wna petla aktualizacji gry.
     */
    void update();

    /**
     * @brief G堯wna petla renderowania gry.
     */
    void render();

    /**
     * @brief Aktualizuje czas deltaTime.
     */
    void updateDeltaTime();

    /**
     * @brief Ustawia teksture otwartego skrzynki.
     */
    void setOpenChestTexture();

    /**
     * @brief Obsluguje wydarzenia w menu.
     */
    void handleMenuEvents();

    /**
     * @brief Obsluguje wydarzenia w ustawieniach.
     */
    void handleSettingsEvents();

    /**
     * @brief Obsluguje wydarzenia podczas gry.
     */
    void handlePlayingEvents();

    /**
     * @brief Obsluguje wydarzenia w menu statystyk.
     */
    void handleStatsMenuEvents();

    /**
     * @brief Aktualizuje stan rozgrywki.
     * @param deltaTime Czas, jaki uplyn像 od ostatniej klatki.
     */
    void updateGameplay(float deltaTime);

    /**
     * @brief Zapisuje stan gry do pliku binarnego.
     * @param filename Nazwa pliku do zapisania.
     */
    void saveToBinaryFile(const std::string& filename);

    /**
     * @brief Wczytuje stan gry z pliku binarnego.
     * @param filename Nazwa pliku do wczytania.
     */
    void loadFromBinaryFile(const std::string& filename);

};

