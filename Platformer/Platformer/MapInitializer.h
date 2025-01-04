#pragma once
#include "stdafx.h"
#include "Obstacle.h"
#include "TextureManager.h"
#include "CollectableItem.h"

class MapInitializer
{
public:

	void initMap1Obstacles(std::vector<Obstacle>& obstacles, TextureManager& textureManager);

	void initMap2Obstacles(std::vector<Obstacle>& obstacles, TextureManager& textureManager);

	void initMap3Obstacles(std::vector<Obstacle>& obstacles, TextureManager& textureManager);

	void initMap4Obstacles(std::vector<Obstacle>& obstacles, TextureManager& textureManager);

	void initMap5Obstacles(std::vector<Obstacle>& obstacles, TextureManager& textureManager);


	void initMap1CollectableItems(std::vector<CollectableItem>& collectableItems, std::vector<CollectableItem> carrotOnTree, TextureManager& textureManager);

	void initMap2CollectableItems(std::vector<CollectableItem>& collectableItems, std::vector<CollectableItem> carrotOnTree, TextureManager& textureManager);

	void initMap3CollectableItems(std::vector<CollectableItem>& collectableItems, std::vector<CollectableItem> carrotOnTree, TextureManager& textureManager);

	void initMap4CollectableItems(std::vector<CollectableItem>& collectableItems, std::vector<CollectableItem> carrotOnTree, TextureManager& textureManager);


	void initMap5CollectableItems(std::vector<CollectableItem>& collectableItems, std::vector<CollectableItem> carrotOnTree, TextureManager& textureManager);

};

