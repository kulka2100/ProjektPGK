#include "stdafx.h"
#include "Player.h"



void Player::initTexture() {
	sf::Texture tempTexture;

    for (int i = 1; i <= 4; i++) {
        if (!tempTexture.loadFromFile("textury/right" + std::to_string(i) + ".png")) {
            std::cout << "Nie uda�o si� za�adowa� tekstury right" + std::to_string(i) + ".png\n";
        }
        this->rightTextures.push_back(tempTexture);
    }

    for (int i = 1; i <= 4; i++) {
        if (!tempTexture.loadFromFile("textury/left" + std::to_string(i) + ".png")) {
            std::cout << "Nie uda�o si� za�adowa� tekstury right" + std::to_string(i) + ".png\n";
        }
        this->leftTextures.push_back(tempTexture);
    }

    for (int i = 1; i <= 4; i++) {
        if (!tempTexture.loadFromFile("textury/up" + std::to_string(i) + ".png")) {
            std::cout << "Nie uda�o si� za�adowa� tekstury right" + std::to_string(i) + ".png\n";
        }
        this->upTextures.push_back(tempTexture);
    }
}

void Player::initSprite() {
    // Sprawd�, czy wektor tekstur nie jest pusty
    if (!this->rightTextures.empty()) {
        // Ustaw pierwsz� klatk� animacji ruchu w prawo jako pocz�tkow� tekstur�
        this->sprite.setTexture(this->rightTextures[0]);
    }
    else {
        std::cout << "Brak tekstur do ustawienia dla sprite'a!\n";
    }

    // Mo�na ustawi� domy�ln� pozycj� sprite'a, je�li chcesz
    this->sprite.setPosition(characterX, characterY); // Przyk�adowa pozycja startowa
	
}



Player::Player(float speed) {
	this->initTexture();
	this->initSprite();
    this->characterSpeed = speed;

    this->animationTimer = 0.0f;
    this->animationTimerMax = 0.1f; // Zmieniaj klatk� co 10 jednostek czasu
    this->animationIndex = 0;
}

Player::~Player()
{
}

void Player::update(float deltaTime) {
    this->animationTimer += deltaTime; // Zwi�kszamy timer co klatk�
    // Sprawd�, czy nale�y zmieni� klatk�
    if (this->animationTimer >= this->animationTimerMax) {
        std::cout << "animiation " << animationIndex << std::endl;

        this->animationIndex++;
        if (this->animationIndex >= this->rightTextures.size()) {
            this->animationIndex = 0;
        }

        // Reset timer
        this->animationTimer = 0.0f;
    }


    // Ruch w prawo
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::D)) {
        this->sprite.move(characterSpeed * deltaTime, 0.0);
        //std::cout << "index " << animationIndex << std::endl;
        this->sprite.setTexture(this->rightTextures[this->animationIndex]);
    }
    // Ruch w lewo
    else if (sf::Keyboard::isKeyPressed(sf::Keyboard::A)) {
        this->sprite.move(-characterSpeed * deltaTime, 0.0);
        this->sprite.setTexture(this->leftTextures[this->animationIndex]);
    }
    else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space)) {
        this->sprite.move(0.0, -50.0 * deltaTime);
        this->sprite.setTexture(this->upTextures[this->animationIndex]);
    }
    else if (sf::Keyboard::isKeyPressed(sf::Keyboard::S)) {
        this->sprite.move(0.0, .3);
    }

}

void Player::render(sf::RenderTarget& target) {
	target.draw(this->sprite);
}

