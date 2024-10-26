#include "stdafx.h"
#include "Player.h"



void Player::initTexture() {
	sf::Texture tempTexture;

    for (int i = 1; i <= 4; i++) {
        if (!tempTexture.loadFromFile("textury/prawo" + std::to_string(i) + ".png")) {
            std::cout << "Nie uda³o siê za³adowaæ tekstury prawo" + std::to_string(i) + ".png\n";
        }
        this->rightTextures.push_back(tempTexture);
    }

    for (int i = 1; i <= 4; i++) {
        if (!tempTexture.loadFromFile("textury/lewo" + std::to_string(i) + ".png")) {
            std::cout << "Nie uda³o siê za³adowaæ tekstury lewo" + std::to_string(i) + ".png\n";
        }
        this->leftTextures.push_back(tempTexture);
    }

    for (int i = 1; i <= 2; i++) {
        if (!tempTexture.loadFromFile("textury/up" + std::to_string(i) + ".png")) {
            std::cout << "Nie uda³o siê za³adowaæ tekstury gora" + std::to_string(i) + ".png\n";
        }
        this->upTextures.push_back(tempTexture);
    }
}

void Player::initSprite() {
    // SprawdŸ, czy wektor tekstur nie jest pusty
    if (!this->rightTextures.empty()) {
        // Ustaw pierwsz¹ klatkê animacji ruchu w prawo jako pocz¹tkow¹ teksturê
        this->playerSprite.setTexture(this->rightTextures[0]);
    }
    else {
        std::cout << "Brak tekstur do ustawienia dla sprite'a!\n";
    }

    // Mo¿na ustawiæ domyœln¹ pozycjê sprite'a, jeœli chcesz
    this->playerSprite.setPosition(sf::Vector2f(playerPosition));
}



Player::Player(sf::Vector2f playerPosition, float speed) {
    this->playerPosition = playerPosition;
    this->characterSpeed = speed;

	this->initTexture();
	this->initSprite();

    this->animationTimer = 0.0f;
    this->animationTimerMax = 0.1f; // Zmieniaj klatkê co 10 jednostek czasu
    this->animationIndex = 0;
}

Player::~Player()
{
}




void Player::update(float deltaTime) {
    this->animationTimer += deltaTime; // Zwiêkszamy timer co klatkê
    // SprawdŸ, czy nale¿y zmieniæ klatkê
    if (this->animationTimer >= this->animationTimerMax) {
        this->animationIndex++;
        if (this->animationIndex >= this->rightTextures.size()) {
            this->animationIndex = 0;
        }
        // Reset timer
        this->animationTimer = 0.0f;
    }

    // Zatrzymywanie postaci gdy dojdzie do krawedzi
    if (getPlayerPosition().x > 700) {
        this->playerSprite.setPosition(700.f, getPlayerPosition().y);
    }
    else if (getPlayerPosition().x < 10) {
       this->playerSprite.setPosition(10.f, getPlayerPosition().y);
    }
    else if (getPlayerPosition().y < 10) {
        this->playerSprite.setPosition(getPlayerPosition().x, 10);
    }

    else if (getPlayerPosition().y > 490) {
       this->playerSprite.setPosition(getPlayerPosition().x, 490);
    }



    // Ruch w prawo
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::D)) {
        this->playerSprite.move(characterSpeed * deltaTime, 0.0);
        this->playerSprite.setTexture(this->rightTextures[this->animationIndex]);
    }
    // Ruch w lewo
    else if (sf::Keyboard::isKeyPressed(sf::Keyboard::A)) {
        this->playerSprite.move(-characterSpeed * deltaTime, 0.0);
        this->playerSprite.setTexture(this->leftTextures[this->animationIndex]);
    }
    else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space)) {
        this->playerSprite.move(0.0, -50.0 * deltaTime);
        this->playerSprite.setTexture(this->upTextures[this->animationIndex]);
    }
    else if (sf::Keyboard::isKeyPressed(sf::Keyboard::S)) {
        this->playerSprite.move(0.0, .3);
    }

    else if (sf::Event::KeyReleased) {
        if (sf::Keyboard::D) {
            this->playerSprite.setTexture(this->rightTextures[0]);
        }
    }


}

void Player::render(sf::RenderTarget& target) {
	target.draw(this->playerSprite);
}

