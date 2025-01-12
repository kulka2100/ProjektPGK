#pragma once
/**
 * @brief Enum reprezentujacy roznne stany gry.
 * Okresla, w jakim trybie aktualnie znajduje sie gra.
 */
enum class GameState {
    Menu,           ///< Stan menu gry, przed rozpoczeciem rozgrywki.
    Playing,        ///< Stan, w ktorym gra jest w trakcie rozgrywki.
    Exiting,        ///< Stan, w ktorym gra jest zamykana.
    ChoosingMaps,   ///< Stan, w ktorym gracz wybiera mapy do gry.
    Settings,       ///< Stan ustawien, w ktorym gracz moze dostosowac parametry gry.
    Pause,          ///< Stan pauzy, w ktorym gra jest wstrzymana.
    Loading,        ///< Stan ladowania, w ktorym gra laduje dane.
    ChoosingStats   ///< Stan, w ktorym gracz wybiera statystyki do przegladu.
};

