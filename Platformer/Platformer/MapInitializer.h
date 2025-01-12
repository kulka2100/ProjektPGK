#pragma once
#include "stdafx.h"
#include "Obstacle.h"
#include "TextureManager.h"
#include "CollectableItem.h"

/**
 * @brief Klasa odpowiedzialna za inicjalizowanie przeszkod i przedmiotow kolekcjonowalnych dla kazdej mapy.
 * Zawiera funkcje do ustawiania danych mapy, takich jak przeszkody i przedmioty do zebrania.
 */
class MapInitializer
{
public:

    /**
    * @brief Inicjalizuje przeszkody dla mapy 1.
    * @param obstacles Wektor, do ktorego zostana dodane przeszkody.
    * @param textureManager Menedzer tekstur, wykorzystywany do ladowania tekstur.
    */
    void initMap1Obstacles(std::vector<Obstacle>& obstacles, TextureManager& textureManager);

    /**
     * @brief Inicjalizuje przeszkody dla mapy 2.
     * @param obstacles Wektor, do ktorego zostana dodane przeszkody.
     * @param textureManager Menedzer tekstur, wykorzystywany do ladowania tekstur.
     */
    void initMap2Obstacles(std::vector<Obstacle>& obstacles, TextureManager& textureManager);

    /**
     * @brief Inicjalizuje przeszkody dla mapy 3.
     * @param obstacles Wektor, do ktorego zostana dodane przeszkody.
     * @param textureManager Menedzer tekstur, wykorzystywany do ladowania tekstur.
     */
    void initMap3Obstacles(std::vector<Obstacle>& obstacles, TextureManager& textureManager);

    /**
     * @brief Inicjalizuje przeszkody dla mapy 4.
     * @param obstacles Wektor, do ktorego zostana dodane przeszkody.
     * @param textureManager Menedzer tekstur, wykorzystywany do ladowania tekstur.
     */
    void initMap4Obstacles(std::vector<Obstacle>& obstacles, TextureManager& textureManager);

    /**
     * @brief Inicjalizuje przeszkody dla mapy 5.
     * @param obstacles Wektor, do ktorego zostana dodane przeszkody.
     * @param textureManager Menedzer tekstur, wykorzystywany do ladowania tekstur.
     */
    void initMap5Obstacles(std::vector<Obstacle>& obstacles, TextureManager& textureManager);


    /**
     * @brief Inicjalizuje przedmioty zbieralne dla mapy 1.
     * @param collectableItems Wektor, do ktorego zostana dodane przedmioty zbieralne.
     * @param carrotOnTree Wektor z przedmiotami typu marchewka na drzewie.
     * @param textureManager Menedzer tekstur, wykorzystywany do ladowania tekstur.
     */
    void initMap1CollectableItems(std::vector<CollectableItem>& collectableItems, std::vector<CollectableItem> carrotOnTree, TextureManager& textureManager);

    /**
     * @brief Inicjalizuje przedmioty zbieralne dla mapy 2.
     * @param collectableItems Wektor, do ktorego zostana dodane przedmioty zbieralne.
     * @param carrotOnTree Wektor z przedmiotami typu marchewka na drzewie.
     * @param textureManager Menedzer tekstur, wykorzystywany do ladowania tekstur.
     */
    void initMap2CollectableItems(std::vector<CollectableItem>& collectableItems, std::vector<CollectableItem> carrotOnTree, TextureManager& textureManager);

    /**
     * @brief Inicjalizuje przedmioty zbieralne dla mapy 3.
     * @param collectableItems Wektor, do ktorego zostana dodane przedmioty zbieralne.
     * @param carrotOnTree Wektor z przedmiotami typu marchewka na drzewie.
     * @param textureManager Menedzer tekstur, wykorzystywany do ladowania tekstur.
     */
    void initMap3CollectableItems(std::vector<CollectableItem>& collectableItems, std::vector<CollectableItem> carrotOnTree, TextureManager& textureManager);

    /**
     * @brief Inicjalizuje przedmioty zbieralne dla mapy 4.
     * @param collectableItems Wektor, do ktorego zostana dodane przedmioty zbieralne.
     * @param carrotOnTree Wektor z przedmiotami typu marchewka na drzewie.
     * @param textureManager Menedzer tekstur, wykorzystywany do ladowania tekstur.
     */
    void initMap4CollectableItems(std::vector<CollectableItem>& collectableItems, std::vector<CollectableItem> carrotOnTree, TextureManager& textureManager);


    /**
     * @brief Inicjalizuje przedmioty zbieralne dla mapy 5.
     * @param collectableItems Wektor, do ktorego zostana dodane przedmioty zbieralne.
     * @param carrotOnTree Wektor z przedmiotami typu marchewka na drzewie.
     * @param textureManager Menedzer tekstur, wykorzystywany do ladowania tekstur.
     */
    void initMap5CollectableItems(std::vector<CollectableItem>& collectableItems, std::vector<CollectableItem> carrotOnTree, TextureManager& textureManager);


};

