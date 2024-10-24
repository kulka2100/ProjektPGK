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


void Background::followPlayer( sf::Vector2f& playerPosition, sf::RenderWindow& window) {

}



void Background::update(float deltaTime) {
    sprite.setPosition(position);
}

void Background::render(sf::RenderTarget& target) {
    target.draw(sprite);
    // Rysowanie dodatkowego sprite'a, aby stworzy� p�ynne przesuwanie t�a
    //Sprawdzenie czy tlo jest przesuwane
    if (speed != 0.0f) {
        sf::Sprite secondSprite = sprite;
        secondSprite.setPosition(position.x + textureBackground.getSize().x, position.y);
        target.draw(secondSprite);
    }
}
