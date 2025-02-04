#include "stdafx.h"
#include "Settings.h"


Settings::Settings(float width, float height) {
	// Ładowanie tekstur do textureManager
	textureManager.loadTexture("textury/easy.png", "easy");
	textureManager.loadTexture("textury/medium.png", "medium");
	textureManager.loadTexture("textury/hard.png", "hard");
	textureManager.loadTexture("textury/back.png", "back");

	settingsTextures = {
	*textureManager.getTexture("easy"),
	*textureManager.getTexture("medium"),
	*textureManager.getTexture("hard"),
	};

	sf::Texture* backTexture = textureManager.getTexture("back");
	if (backTexture) {
		backSprite.setTexture(*backTexture);
		backSprite.setPosition(sf::Vector2f(50.f, 35.f));
	}

	background = new Background("textury/settings.png");


	float margin = 20.0f;  // Margines pomiędzy sprite'ami
	float totalHeight = settingsTextures.size() * settingsTextures[0].getSize().y + (settingsTextures.size() - 1) * margin; // Całkowita wysokość z marginesami

	float startY = (height - totalHeight) / 2.0f; // Początkowa Y, aby wycentrować na osi Y

	for (const auto& texture : settingsTextures) {
		sf::Sprite sprite;
		sprite.setTexture(texture);

		// Ustawianie pozycji X, aby wycentrować na szerokości okna
		float startX = width / 2.0f - sprite.getGlobalBounds().width / 2.0f;

		// Ustawianie pozycji Y z zachowaniem marginesów
		sprite.setPosition(sf::Vector2f(startX + 18.f, startY + 30.f));

		// Dodawanie sprite'a do kontenera
		settingsItems.push_back(sprite);

		// Zwiększanie pozycji Y dla kolejnego sprite'a z uwzględnieniem marginesu
		startY += sprite.getGlobalBounds().height + margin;
	}
}


std::vector <sf::Sprite>& Settings::getItems() {
	return settingsItems;
}

void Settings::draw(sf::RenderWindow& window) {
	background->render(window);
	window.draw(backSprite);
	for (const auto& item : settingsItems) {
		window.draw(item);
	}
}