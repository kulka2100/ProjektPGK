#include "stdafx.h"
#include "Background.h"

Background::Background(const std::string& filename, Player *player){
    this->player = player;
    std::cout << "Próba za³adowania pliku: " << filename << std::endl;
	if (!textureBackground.loadFromFile(filename)) {
		throw std::runtime_error("Nie mo¿na za³adowaæ tekstury: ");
	}
    backgroundSprite.setTexture(textureBackground);
	position = sf::Vector2f(0.0f, 0.0f);
}


Background::Background(const std::string& filename) {
    std::cout << "Próba za³adowania pliku: " << filename << std::endl;
    if (!textureBackground.loadFromFile(filename)) {
        throw std::runtime_error("Nie mo¿na za³adowaæ tekstury: ");
    }
    backgroundSprite.setTexture(textureBackground);
    position = sf::Vector2f(0.0f, 0.0f);
}


sf::Sprite& Background::getBackgroundSprite() {
    return backgroundSprite;
}

sf::Texture& Background::getBackgroundTexture() {
    return textureBackground;
}

void Background::update(float deltaTime, float characterSpeed) {
    // Aktualizujemy pozycjê sprite'a na podstawie nowej pozycji
    //Przesuwanie tla

    if (player->getPlayerPosition().x > 700  && abs(position.x) < textureBackground.getSize().x) {
        position.x -= characterSpeed * deltaTime;
        // Aktualizujemy pozycjê sprite'a na podstawie nowej pozycji
        backgroundSprite.setPosition(position);
        isUpdated = true;
        moveRight = true;

    }
    else if (player->getPlayerPosition().x < 10  && position.x < 0) {
        position.x += characterSpeed * deltaTime;
        // Aktualizujemy pozycjê sprite'a na podstawie nowej pozycji
        backgroundSprite.setPosition(position);
        isUpdated = true;
        moveLeft = true;
    }
    else {
        isUpdated = false;
        moveLeft = false;
        moveRight = false;

    }

    backgroundSprite.setPosition(position);
}

void Background::render(sf::RenderTarget& target) {
    target.draw(backgroundSprite);
    // Rysowanie dodatkowego sprite'a, aby stworzyæ p³ynne przesuwanie t³a
    //Sprawdzenie czy tlo jest przesuwane
    if (speed != 0.0f) {
        sf::Sprite secondSprite = backgroundSprite;
        secondSprite.setPosition(position.x + textureBackground.getSize().x, position.y);
        target.draw(secondSprite);
    }
}
