#include "stdafx.h"
#include "Background.h"

Background::Background(const std::string& filename){
    std::cout << "Pr�ba za�adowania pliku: " << filename << std::endl;
	if (!textureBackground.loadFromFile(filename)) {
		throw std::runtime_error("Nie mo�na za�adowa� tekstury: ");
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
    // Przesuwanie t�a, je�li jest ustawiona pr�dko��
    if (speed != 0.0f) {
        position.x -= speed * deltaTime;

        // Je�li t�o przesunie si� za ekran, zresetuj pozycj�
        if (position.x + textureBackground.getSize().x <= 0) {
            position.x = 0;
        }

        sprite.setPosition(position);
    }
}

void Background::render(sf::RenderTarget& target) {
    target.draw(sprite);
    // Rysowanie dodatkowego sprite'a, aby stworzy� p�ynne przesuwanie t�a
    if (speed != 0.0f) {
        sf::Sprite secondSprite = sprite;
        secondSprite.setPosition(position.x + textureBackground.getSize().x, position.y);
        target.draw(secondSprite);
    }
}
