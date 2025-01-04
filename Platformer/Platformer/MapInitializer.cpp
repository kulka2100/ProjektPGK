#include "stdafx.h"
#include "MapInitializer.h"


void MapInitializer::initMap1Obstacles(std::vector<Obstacle>& obstacles, TextureManager& textureManager) {
	textureManager.loadTexture("textury/las/platforma.png", "platformaLas");
	textureManager.loadTexture("textury/las/malaPlatforma.png", "malaPlatformaLas");
	textureManager.loadTexture("textury/las/kamyk.png", "kamykLas");
	// Pobieranie wskaŸnika do tekstury
	sf::Texture* platformTexture = textureManager.getTexture("platformaLas");
	sf::Texture* smallPlatformTexture = textureManager.getTexture("malaPlatformaLas");
	sf::Texture* kamykTexture = textureManager.getTexture("kamykLas");

	if (platformTexture) {
		// Dodawanie przeszkód z za³adowan¹ tekstur¹
		obstacles.emplace_back(*platformTexture, sf::Vector2f(50, 200.f), ObstacleType::Platform);
		obstacles.emplace_back(*platformTexture, sf::Vector2f(500.f, 250.f), ObstacleType::Platform);
	}
	if (kamykTexture) {
		obstacles.emplace_back(*kamykTexture, sf::Vector2f(700.f, 400.0f), ObstacleType::Stone);
	}
	else {
		std::cerr << "Tekstura platforma nie zosta³a poprawnie za³adowana." << platformTexture << std::endl;
	}
	if (smallPlatformTexture) {
		obstacles.emplace_back(*smallPlatformTexture, sf::Vector2f(250.f, 380.f), ObstacleType::Platform);
	}
}

void MapInitializer::initMap2Obstacles(std::vector<Obstacle>& obstacles, TextureManager& textureManager) {
	textureManager.loadTexture("textury/polana/platforma.png", "platformaPolana");
	textureManager.loadTexture("textury/polana/malaPlatforma.png", "malaPlatformaPolana");

	sf::Texture* platformTexture = textureManager.getTexture("platformaPolana");
	sf::Texture* smallPlatformTexture = textureManager.getTexture("malaPlatformaPolana");

	if (platformTexture) {
		// Dodawanie przeszkód z za³adowan¹ tekstur¹
		obstacles.emplace_back(*platformTexture, sf::Vector2f(50, 200.f), ObstacleType::Platform);
		obstacles.emplace_back(*platformTexture, sf::Vector2f(500.f, 250.f), ObstacleType::Platform);
	}
	if (smallPlatformTexture) {
		obstacles.emplace_back(*smallPlatformTexture, sf::Vector2f(550.f, 380.f), ObstacleType::Platform);
	}
}

void MapInitializer::initMap3Obstacles(std::vector<Obstacle>& obstacles, TextureManager& textureManager) {
	textureManager.loadTexture("textury/wulkan/platforma.png", "platformaWulkan");
	textureManager.loadTexture("textury/wulkan/smallBox.png", "smallBoxWulkan");
	textureManager.loadTexture("textury/wulkan/stone.png", "stoneWulkan");

	sf::Texture* platformTexture = textureManager.getTexture("platformaWulkan");
	sf::Texture* smallBoxTexture = textureManager.getTexture("smallBoxWulkan");
	sf::Texture* stoneWulkan = textureManager.getTexture("stoneWulkan");

	if (platformTexture) {
		// Dodawanie przeszkód z za³adowan¹ tekstur¹
		obstacles.emplace_back(*platformTexture, sf::Vector2f(50, 200.f), ObstacleType::Platform);
		obstacles.emplace_back(*platformTexture, sf::Vector2f(500.f, 250.f), ObstacleType::Platform);
	}
	if (smallBoxTexture) {
		obstacles.emplace_back(*smallBoxTexture, sf::Vector2f(550.f, 400.f), ObstacleType::Stone);

	}
	//Dodac spadanie g³azów
	if (stoneWulkan) {
		obstacles.emplace_back(*stoneWulkan, sf::Vector2f(300.f, 10.f), ObstacleType::FallingStone);
		obstacles.emplace_back(*stoneWulkan, sf::Vector2f(600.f, 100.f), ObstacleType::FallingStone);

	}
}

void MapInitializer::initMap4Obstacles(std::vector<Obstacle>& obstacles, TextureManager& textureManager) {
	textureManager.loadTexture("textury/pieklo/platforma.png", "platformaPielko");
	textureManager.loadTexture("textury/pieklo/kolce.png", "kolce");
	textureManager.loadTexture("textury/pieklo/kosa.png", "kosa");

	sf::Texture* platformTexture = textureManager.getTexture("platformaPielko");
	sf::Texture* kolceTexture = textureManager.getTexture("kolce");
	sf::Texture* kosaWulkan = textureManager.getTexture("kosa");

	if (platformTexture) {
		// Dodawanie przeszkód z za³adowan¹ tekstur¹
		obstacles.emplace_back(*platformTexture, sf::Vector2f(50, 200.f), ObstacleType::Platform);
		obstacles.emplace_back(*platformTexture, sf::Vector2f(500.f, 250.f), ObstacleType::Platform);
	}
	if (kolceTexture) {
		obstacles.emplace_back(*kolceTexture, sf::Vector2f(550.f, 450.f), ObstacleType::Spikes);
	}
	//Zrobic poruszanie kos¹
	if (kosaWulkan) {
		obstacles.emplace_back(*kosaWulkan, sf::Vector2f(400.f, 200.f), ObstacleType::Scythe);
	}
}

void MapInitializer::initMap5Obstacles(std::vector<Obstacle>& obstacles, TextureManager& textureManager) {
	textureManager.loadTexture("textury/niebo/column.png", "columnNiebo");
	sf::Texture* columnTexture = textureManager.getTexture("columnNiebo");

	if (columnTexture) {
		// Dodawanie przeszkód z za³adowan¹ tekstur¹
		obstacles.emplace_back(*columnTexture, sf::Vector2f(500, 100.f), ObstacleType::Stone);
		obstacles.emplace_back(*columnTexture, sf::Vector2f(1300, 100.f), ObstacleType::Stone);
	}
}


void MapInitializer::initMap1CollectableItems(std::vector<CollectableItem>& collectableItems, std::vector<CollectableItem> carrotOnTree, TextureManager& textureManager) {
	textureManager.loadTexture("textury/las/marchewka.png", "marchewka");
	textureManager.loadTexture("textury/hp.png", "health");
	textureManager.loadTexture("textury/las/key.png", "key");
	textureManager.loadTexture("textury/las/chest.png", "chest");
	textureManager.loadTexture("textury/las/tree.png", "tree");
	textureManager.loadTexture("textury/gate.png", "gate");
	
	sf::Texture* marchewkaTexture = textureManager.getTexture("marchewka");
	sf::Texture* healthTexture = textureManager.getTexture("health");
	sf::Texture* keyTexture = textureManager.getTexture("key");
	sf::Texture* chestTexture = textureManager.getTexture("chest");
	sf::Texture* treeTexture = textureManager.getTexture("tree");
	sf::Texture* gateTexture = textureManager.getTexture("gate");


	if (marchewkaTexture) {
		collectableItems.emplace_back(*marchewkaTexture, sf::Vector2f(400.f, 400.0f), ItemType::Carrot);
		collectableItems.emplace_back(*marchewkaTexture, sf::Vector2f(200.f, 400.0f), ItemType::Carrot);
		collectableItems.emplace_back(*marchewkaTexture, sf::Vector2f(1400.f, 170.f), ItemType::Carrot);
	}
	else {
		std::cerr << "Tekstura marchewki nie zosta³a poprawnie za³adowana." << marchewkaTexture << std::endl;
	}
	if (healthTexture) {
		collectableItems.emplace_back(*healthTexture, sf::Vector2f(400.f, 230.f), ItemType::Health);
		collectableItems.emplace_back(*healthTexture, sf::Vector2f(200.f, 230.f), ItemType::Health);
		collectableItems.emplace_back(*healthTexture, sf::Vector2f(450.f, 230.f), ItemType::Health);
		collectableItems.emplace_back(*healthTexture, sf::Vector2f(100.f, 400.f), ItemType::Health);
		collectableItems.emplace_back(*healthTexture, sf::Vector2f(150.f, 230.f), ItemType::Health);
	}
	else {
		std::cerr << "Tekstura hp nie zosta³a poprawnie za³adowana." << healthTexture << std::endl;
	}
	if (keyTexture) {
		collectableItems.emplace_back(*keyTexture, sf::Vector2f(750.f, 330.f), ItemType::Key);
	}
	else {
		std::cerr << "Tekstura key nie zosta³a poprawnie za³adowana." << keyTexture << std::endl;
	}

	if (chestTexture) {
		collectableItems.emplace_back(*chestTexture, sf::Vector2f(1300.f, 330.f), ItemType::Chest);
	}
	else {
		std::cerr << "Tekstura chest nie zosta³a poprawnie za³adowana." << chestTexture << std::endl;
	}

	if (treeTexture && marchewkaTexture) {
		collectableItems.emplace_back(*treeTexture, sf::Vector2f(1000.f, 150.f), ItemType::Tree);
		// Uzyskanie referencji do ostatnio dodanego elementu (drzewa)
		carrotOnTree.emplace_back(*marchewkaTexture, sf::Vector2f(1100.f, 170.f), ItemType::Carrot);
		carrotOnTree.emplace_back(*marchewkaTexture, sf::Vector2f(1100.f, 270.f), ItemType::Carrot);
		carrotOnTree.emplace_back(*marchewkaTexture, sf::Vector2f(1200.f, 200.f), ItemType::Carrot);
	}
	else {
		std::cerr << "Tekstura chest nie zosta³a poprawnie za³adowana." << treeTexture << std::endl;
	}
	if (gateTexture) {
		collectableItems.emplace_back(*gateTexture, sf::Vector2f(2100.f, 255.f), ItemType::Gate);
	}
	else {
		std::cerr << "Tekstura chest nie zosta³a poprawnie za³adowana." << gateTexture << std::endl;
	}
}

void MapInitializer::initMap2CollectableItems(std::vector<CollectableItem>& collectableItems, std::vector<CollectableItem> carrotOnTree, TextureManager& textureManager) {
	textureManager.loadTexture("textury/polana/marchewka.png", "marchewkaPolana");
	textureManager.loadTexture("textury/hp.png", "health");
	textureManager.loadTexture("textury/polana/key.png", "keyPolana");
	textureManager.loadTexture("textury/polana/chest.png", "chestPolana");

	sf::Texture* marchewkaTexture = textureManager.getTexture("marchewkaPolana");
	sf::Texture* healthTexture = textureManager.getTexture("health");
	sf::Texture* keyTexture = textureManager.getTexture("keyPolana");
	sf::Texture* chestTexture = textureManager.getTexture("chestPolana");
	sf::Texture* gateTexture = textureManager.getTexture("gate");


	if (marchewkaTexture) {
		collectableItems.emplace_back(*marchewkaTexture, sf::Vector2f(400.f, 400.0f), ItemType::Carrot);
		collectableItems.emplace_back(*marchewkaTexture, sf::Vector2f(200.f, 400.0f), ItemType::Carrot);
		collectableItems.emplace_back(*marchewkaTexture, sf::Vector2f(1400.f, 170.f), ItemType::Carrot);
	}
	else {
		std::cerr << "Tekstura marchewki nie zosta³a poprawnie za³adowana." << marchewkaTexture << std::endl;
	}
	if (healthTexture) {
		collectableItems.emplace_back(*healthTexture, sf::Vector2f(400.f, 230.f), ItemType::Health);
		collectableItems.emplace_back(*healthTexture, sf::Vector2f(200.f, 230.f), ItemType::Health);
	}
	else {
		std::cerr << "Tekstura hp nie zosta³a poprawnie za³adowana." << healthTexture << std::endl;
	}
	if (keyTexture) {
		collectableItems.emplace_back(*keyTexture, sf::Vector2f(750.f, 330.f), ItemType::Key);
	}
	else {
		std::cerr << "Tekstura key nie zosta³a poprawnie za³adowana." << keyTexture << std::endl;
	}

	if (chestTexture) {
		collectableItems.emplace_back(*chestTexture, sf::Vector2f(1300.f, 380.f), ItemType::Chest);
	}
	else {
		std::cerr << "Tekstura chest nie zosta³a poprawnie za³adowana." << chestTexture << std::endl;
	}
	if (gateTexture) {
		collectableItems.emplace_back(*gateTexture, sf::Vector2f(2100.f, 255.f), ItemType::Gate);
	}
	else {
		std::cerr << "Tekstura chest nie zosta³a poprawnie za³adowana." << gateTexture << std::endl;
	}
}

void MapInitializer::initMap3CollectableItems(std::vector<CollectableItem>& collectableItems, std::vector<CollectableItem> carrotOnTree, TextureManager& textureManager) {
	textureManager.loadTexture("textury/polana/marchewka.png", "marchewkaPolana");
	textureManager.loadTexture("textury/hp.png", "health");
	textureManager.loadTexture("textury/las/key.png", "keyPolana");
	textureManager.loadTexture("textury/wulkan/chest.png", "chestWulkan");

	sf::Texture* marchewkaTexture = textureManager.getTexture("marchewkaPolana");
	sf::Texture* healthTexture = textureManager.getTexture("health");
	sf::Texture* keyTexture = textureManager.getTexture("keyPolana");
	sf::Texture* chestTexture = textureManager.getTexture("chestWulkan");
	sf::Texture* gateTexture = textureManager.getTexture("gate");


	if (marchewkaTexture) {
		collectableItems.emplace_back(*marchewkaTexture, sf::Vector2f(400.f, 400.0f), ItemType::Carrot);
		collectableItems.emplace_back(*marchewkaTexture, sf::Vector2f(200.f, 400.0f), ItemType::Carrot);
		collectableItems.emplace_back(*marchewkaTexture, sf::Vector2f(1400.f, 170.f), ItemType::Carrot);
	}
	else {
		std::cerr << "Tekstura marchewki nie zosta³a poprawnie za³adowana." << marchewkaTexture << std::endl;
	}
	if (healthTexture) {
		collectableItems.emplace_back(*healthTexture, sf::Vector2f(400.f, 230.f), ItemType::Health);
		collectableItems.emplace_back(*healthTexture, sf::Vector2f(200.f, 230.f), ItemType::Health);
	}
	else {
		std::cerr << "Tekstura hp nie zosta³a poprawnie za³adowana." << healthTexture << std::endl;
	}
	if (keyTexture) {
		collectableItems.emplace_back(*keyTexture, sf::Vector2f(750.f, 330.f), ItemType::Key);
	}
	else {
		std::cerr << "Tekstura key nie zosta³a poprawnie za³adowana." << keyTexture << std::endl;
	}

	if (chestTexture) {
		collectableItems.emplace_back(*chestTexture, sf::Vector2f(1300.f, 330.f), ItemType::Chest);
	}
	else {
		std::cerr << "Tekstura chest nie zosta³a poprawnie za³adowana." << chestTexture << std::endl;
	}
	if (gateTexture) {
		collectableItems.emplace_back(*gateTexture, sf::Vector2f(2100.f, 255.f), ItemType::Gate);
	}
	else {
		std::cerr << "Tekstura chest nie zosta³a poprawnie za³adowana." << gateTexture << std::endl;
	}

}
void MapInitializer::initMap4CollectableItems(std::vector<CollectableItem>& collectableItems, std::vector<CollectableItem> carrotOnTree, TextureManager& textureManager) {
	sf::Texture* gateTexture = textureManager.getTexture("gate");


	if (gateTexture) {
		collectableItems.emplace_back(*gateTexture, sf::Vector2f(2100.f, 255.f), ItemType::Gate);
	}
	else {
		std::cerr << "Tekstura chest nie zosta³a poprawnie za³adowana." << gateTexture << std::endl;
	}
}


void MapInitializer::initMap5CollectableItems(std::vector<CollectableItem>& collectableItems, std::vector<CollectableItem> carrotOnTree, TextureManager& textureManager) {
	textureManager.loadTexture("textury/polana/marchewka.png", "marchewkaPolana");
	textureManager.loadTexture("textury/hp.png", "health");
	textureManager.loadTexture("textury/las/key.png", "keyPolana");

	sf::Texture* marchewkaTexture = textureManager.getTexture("marchewkaPolana");
	sf::Texture* healthTexture = textureManager.getTexture("health");
	sf::Texture* keyTexture = textureManager.getTexture("keyPolana");
	sf::Texture* gateTexture = textureManager.getTexture("gate");


	if (marchewkaTexture) {
		collectableItems.emplace_back(*marchewkaTexture, sf::Vector2f(400.f, 400.0f), ItemType::Carrot);
		collectableItems.emplace_back(*marchewkaTexture, sf::Vector2f(200.f, 400.0f), ItemType::Carrot);
		collectableItems.emplace_back(*marchewkaTexture, sf::Vector2f(1400.f, 170.f), ItemType::Carrot);
	}
	else {
		std::cerr << "Tekstura marchewki nie zosta³a poprawnie za³adowana." << marchewkaTexture << std::endl;
	}
	if (healthTexture) {
		collectableItems.emplace_back(*healthTexture, sf::Vector2f(400.f, 230.f), ItemType::Health);
		collectableItems.emplace_back(*healthTexture, sf::Vector2f(200.f, 230.f), ItemType::Health);
	}
	else {
		std::cerr << "Tekstura hp nie zosta³a poprawnie za³adowana." << healthTexture << std::endl;
	}
	if (keyTexture) {
		collectableItems.emplace_back(*keyTexture, sf::Vector2f(750.f, 330.f), ItemType::Key);
	}
	else {
		std::cerr << "Tekstura key nie zosta³a poprawnie za³adowana." << keyTexture << std::endl;
	}

	if (gateTexture) {
		collectableItems.emplace_back(*gateTexture, sf::Vector2f(2100.f, 255.f), ItemType::Gate);
	}
	else {
		std::cerr << "Tekstura chest nie zosta³a poprawnie za³adowana." << gateTexture << std::endl;
	}
}
