#include "stdafx.h"
#include "Player.h"



void Player::initTexture() {
	sf::Texture tempTexture;

    for (int i = 1; i <= 5; i++) {
        if (!tempTexture.loadFromFile("textury/prawo" + std::to_string(i) + ".png")) {
            std::cout << "Nie uda³o siê za³adowaæ tekstury prawo" + std::to_string(i) + ".png\n";
        }
        this->rightTextures.push_back(tempTexture);
    }

    for (int i = 1; i <= 5; i++) {
        if (!tempTexture.loadFromFile("textury/lewo" + std::to_string(i) + ".png")) {
            std::cout << "Nie uda³o siê za³adowaæ tekstury lewo" + std::to_string(i) + ".png\n";
        }
        this->leftTextures.push_back(tempTexture);
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

    bulletTexture.loadFromFile("textury/bullet1.png");
	this->initTexture();
	this->initSprite();

    this->animationTimer = 0.0f;
    this->animationTimerMax = 0.1f; // Zmieniaj klatkê co 10 jednostek czasu
    this->animationIndex = 0;
}

Player::~Player()
{
}

void Player::updateAnimations(float deltaTime) {
    {
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
    }
}


void Player::holdPlayerAtEdges() {
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
}


void Player::shoot() {
    // Pozycja pocisku zaczyna siê przy postaci
    sf::Vector2f startPos = this->playerSprite.getPosition();
    // Kierunek, np. strza³ w prawo
    sf::Vector2f direction(bulletDir, 0.0f);
    bullets.emplace_back(bulletTexture, startPos, direction, 200.f);
}

void Player::gravitation(float deltaTime) {
    if (isJumping) {
        verticalVelocity += GRAVITY * deltaTime;
        playerSprite.move(0, verticalVelocity);

        // Sprawdzanie, czy postaæ dotknê³a ziemi
        if (playerSprite.getPosition().y >= playerPosition.y) {
            playerSprite.setPosition(playerSprite.getPosition().x, playerPosition.y);
            verticalVelocity = 0;
            isJumping = false;
        }
    }
}



void Player::update(float deltaTime, sf::Event &event) {
    //Animowanie textur
    updateAnimations(deltaTime);

    // Zatrzymywanie postaci gdy dojdzie do krawedzi
    holdPlayerAtEdges();


    // Ruch w prawo
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::D)) {
        //Skok podczas ruchu w prawo
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::W) && !isJumping) {
            verticalVelocity = JUMP_STRENGTH;
            isJumping = true;
        }
        this->playerSprite.move(characterSpeed * deltaTime, 0.0);
        this->playerSprite.setTexture(this->rightTextures[this->animationIndex]);
        bulletDir = 1.0;
    }
    // Ruch w lewo
    else if (sf::Keyboard::isKeyPressed(sf::Keyboard::A)) {
        //Skok podczas ruchu w lewo
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::W) && !isJumping) {
            verticalVelocity = JUMP_STRENGTH;
            isJumping = true;
        }
        this->playerSprite.move(-characterSpeed * deltaTime, 0.0);
        this->playerSprite.setTexture(this->leftTextures[this->animationIndex]);
        bulletDir = -1.0;
    }
    //Skok
    else if (sf::Keyboard::isKeyPressed(sf::Keyboard::W) && !isJumping) {
        verticalVelocity = JUMP_STRENGTH;
        isJumping = true;
     
    }
    //Strzaly
    else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space)) {
        shoot();
    }

    if (event.type == sf::Event::KeyReleased) {
        if (event.key.code == sf::Keyboard::D) {
            this->playerSprite.setTexture(this->rightTextures[0]);
        }
        else if (event.key.code == sf::Keyboard::A) {
            this->playerSprite.setTexture(this->leftTextures[0]);
        }
    }

    // Dodawanie grawitacji, aby postaæ wraca³a na ziemiê
    gravitation(deltaTime);

    //Akutalizacja pociskow
    for (auto it = bullets.begin(); it != bullets.end(); ) {
        it->update(deltaTime);
        if (it->isOffScreen()) {  // Dodaj metodê `isOffScreen()` w klasie Bullet
            it = bullets.erase(it); // Usuñ pocisk, jeœli jest poza ekranem
        }
        else {
            ++it;
        }
    }

}

    void Player::render(sf::RenderTarget &target) {
        target.draw(this->playerSprite);

        for (auto& bullet : bullets) {
            bullet.render(&target);
        }
    }


