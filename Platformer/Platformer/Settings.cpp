#include "stdafx.h"
#include "Settings.h"


Settings::Settings(float width, float height) {
	// £adowanie tekstur do textureManager
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


	float margin = 20.0f;  // Margines pomiêdzy sprite'ami
	float totalHeight = settingsTextures.size() * settingsTextures[0].getSize().y + (settingsTextures.size() - 1) * margin; // Ca³kowita wysokoœæ z marginesami

	float startY = (height - totalHeight) / 2.0f; // Pocz¹tkowa Y, aby wycentrowaæ na osi Y

	for (const auto& texture : settingsTextures) {
		sf::Sprite sprite;
		sprite.setTexture(texture);

		// Ustawianie pozycji X, aby wycentrowaæ na szerokoœci okna
		float startX = width / 2.0f - sprite.getGlobalBounds().width / 2.0f;

		// Ustawianie pozycji Y z zachowaniem marginesów
		sprite.setPosition(sf::Vector2f(startX + 18.f, startY + 30.f));

		// Dodawanie sprite'a do kontenera
		settingsItems.push_back(sprite);

		// Zwiêkszanie pozycji Y dla kolejnego sprite'a z uwzglêdnieniem marginesu
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