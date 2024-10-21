#include "stdafx.h"
#include "Background.h"

Background::Background(const std::string& filename){
    std::cout << "Próba za³adowania pliku: " << filename << std::endl;
	if (!textureBackground.loadFromFile(filename)) {
		throw std::runtime_error("Nie mo¿na za³adowaæ tekstury: ");
	}
	sprite.setTexture(textureBackground);
	position = sf::Vector2f(0.0f, 0.0f);
}

void Background::adjustBackground(sf::RenderWindow& window) {
    sf::Vector2u textureSize = textureBackground.getSize();
    sf::Vector2u windowSize = window.getSize();

    sprite.setScale(
        float(windowSize.x) / textureSize.x,
        float(windowSize.y) / textureSize.y
    );
}

void Background::update(float deltaTime) {
    // Przesuwanie t³a, jeœli jest ustawiona prêdkoœæ
    if (speed != 0.0f) {
        position.x -= speed * deltaTime;

        // Jeœli t³o przesunie siê za ekran, zresetuj pozycjê
        if (position.x + textureBackground.getSize().x <= 0) {
            position.x = 0;
        }

        sprite.setPosition(position);
    }
}

void Background::render(sf::RenderTarget& target) {
    target.draw(sprite);
    // Rysowanie dodatkowego sprite'a, aby stworzyæ p³ynne przesuwanie t³a
    if (speed != 0.0f) {
        sf::Sprite secondSprite = sprite;
        secondSprite.setPosition(position.x + textureBackground.getSize().x, position.y);
        target.draw(secondSprite);
    }
}
