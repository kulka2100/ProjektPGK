#include "stdafx.h"
#include "Player.h"


void Player::initTexture() {
    // �adowanie tekstur ruchu w prawo
    for (int i = 1; i <= 5; i++) {
        std::string textureKey = "prawo" + std::to_string(i);
        std::string filePath = "textury/" + textureKey + ".png";

        textureManager.loadTexture(filePath, textureKey);

        // Pobranie tekstury z managera i dodanie do wektora
        sf::Texture* texture = textureManager.getTexture(textureKey);
        if (texture) {
            rightTextures.push_back(*texture);
        }
        else {
            std::cout << "Nie uda�o si� za�adowa� tekstury: " << filePath << "\n";
        }
    }

    // �adowanie tekstur ruchu w lewo
    for (int i = 1; i <= 5; i++) {
        std::string textureKey = "lewo" + std::to_string(i);
        std::string filePath = "textury/" + textureKey + ".png";

        textureManager.loadTexture(filePath, textureKey);

        // Pobranie tekstury z managera i dodanie do wektora
        sf::Texture* texture = textureManager.getTexture(textureKey);
        if (texture) {
            leftTextures.push_back(*texture);
        }
        else {
            std::cout << "Nie uda�o si� za�adowa� tekstury: " << filePath << "\n";
        }
    }
    
    // �adowanie tekstury HP
    textureManager.loadTexture("textury/hp.png", "hp");

    sf::Texture* hpTexture = textureManager.getTexture("hp");
    if (hpTexture) {
        for (int i = 0; i < getCurrentHealth(); i++) {
            hpTextures.push_back(*hpTexture);
        }
    }
    else {
        std::cout << "Nie uda�o si� za�adowa� tekstury HP: " << "textury/hp.png" << "\n";
    }

    if (!amuTexture.loadFromFile("textury/amu.png")) {
        std::cout << "Nie uda�o si� za�adowa� tekstury amunicji" << std::endl;
    }

}

void Player::initSprite() { 
    // Sprawdz, czy wektor tekstur nie jest pusty
    if (!this->rightTextures.empty()) {
        // Ustaw pierwsza klatke animacji ruchu w prawo jako pocz�tkow� tekstur�
        this->playerSprite.setTexture(this->rightTextures[0]);
    }
    if (!this->hpTextures.empty()) {
        this->hpSprite.resize(getCurrentHealth()); // Zainicjujemy 3 sprite'y
        for (int i = 0; i < hpTextures.size(); i++) {
            this->hpSprite[i].setTexture(this->hpTextures[i]);
            float step = i * 45;
            this->hpSprite[i].setPosition(sf::Vector2f(30.f + step, 25.f));
        }     
    }
    else {
        std::cout << "Brak tekstur do ustawienia dla sprite'a!\n";
    }
    this->amuSprite.setTexture(amuTexture);
    this->amuSprite.setPosition(sf::Vector2f(720.f, 25.f));
    this->playerSprite.setPosition(sf::Vector2f(playerPosition));
}

void Player::initText() {
    if (!font.loadFromFile("font.ttf")) {
        std::cout << "Nie uda�o si� za�adowa� czcionki!" << std::endl;
    }
    ammoText.setFont(font);
    ammoText.setCharacterSize(26);        // Rozmiar tekstu
    ammoText.setString(std::to_string(currentAmmo));
    ammoText.setFillColor(sf::Color::White); // Kolor tekstu
    ammoText.setPosition(770.f, 25.f);    // Pozycja tekstu obok amuSprite
}


Player::Player(sf::Vector2f playerPosition, int hp) : health(hp) {
    this->playerPosition = playerPosition;

    bulletTexture.loadFromFile("textury/bullet1.png");
	this->initTexture();
    this->initText();
	this->initSprite();
    this->isJumping = false;  
    this->isOnGround = true;

    this->animationTimer = 0.0f;
    this->animationTimerMax = 0.1f; // Zmieniaj klatk� co 10 jednostek czasu
    this->animationIndex = 0;

    //Strzaly
    this->shootCooldown = 0.0f;
    this->shootCooldownMax = 0.5f;

    this->experience = 0;
    this->level = 1;
    this->experienceToNext = 100;
    this->maxHealth = 5;
    this->damage = 1;
    this->characterSpeed = 500.f;

    //experience(0), level(1), experienceToNext(100), maxHealth(100), damage(10), speed(200.f)
}

Player::~Player()
{
}

void Player::updateAnimations(float deltaTime) {
    {
        this->animationTimer += deltaTime; // Zwi�kszamy timer co klatk�
        // Sprawd�, czy nale�y zmieni� klatk�
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
    if (getPlayerPosition().x > 600) {
        this->playerSprite.setPosition(600.f, getPlayerPosition().y);
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
    // Pozycja pocisku zaczyna si� przy postaci
    sf::Vector2f startPos = this->playerSprite.getPosition();

    // Kierunek, np. strza� w prawo
    sf::Vector2f direction(bulletDir, 0.0f);

    if (currentAmmo > 0) {
        bullets.emplace_back(bulletTexture, startPos, direction, 400.f);
        std::cout << currentAmmo;
        currentAmmo--;
        updateAmmoText(currentAmmo);
    }
}

void Player::gravitation(float deltaTime) {
    // Je�li gracz nie dotyka ziemi ani platformy, zastosuj grawitacj�
    if (!isOnGround) {
        verticalVelocity += GRAVITY * deltaTime;
        playerSprite.move(0, verticalVelocity * deltaTime);

        // Sprawdzanie, czy posta� dotkn�a ziemi
        if (playerSprite.getPosition().y >= playerPosition.y) {
            playerSprite.setPosition(playerSprite.getPosition().x, playerPosition.y);
            verticalVelocity = 0;
            isJumping = false;
            isOnGround = true;
        }
    
    } 

}

void Player::setOnGround(bool isOnGround) {
    this->isOnGround = isOnGround;
}

void Player::setVerticalVelocity(float verticalVelocity) {
    this->verticalVelocity = verticalVelocity;
}

void Player::setIsJumping(bool jumping) {
    this->isJumping = jumping;
}


void Player::updateHealth(int count) {
    if (!hpTextures.empty()) {
        for (int i = 0; i < count; ++i) {
            health++;
            sf::Sprite newSprite;
            newSprite.setTexture(hpTextures[0]);

            // Pobranie pozycji ostatniego sprita z vectora hpSprite
            sf::Vector2f lastPosition;
            if (!hpSprite.empty()) {
                lastPosition = hpSprite.back().getPosition();
            }
            else {
                lastPosition = sf::Vector2f(0.f, 25.f); // Ustawienie domyślnej pozycji, jeśli brak sprite'ów
            }

            newSprite.setPosition(sf::Vector2f(lastPosition.x + 45, 25.f));
            hpSprite.push_back(newSprite);
        }
    }
    else {
        std::cerr << "hpTextures jest pusty! Nie mo�na doda� sprite'a." << std::endl;
    }
}

void Player::updateAmmoText(int currentAmmo) {
    ammoText.setString(std::to_string(currentAmmo));
}

void Player::update(float deltaTime, sf::Event &event) {
    bool isOnPlatform = false;
    //Animowanie textur
    updateAnimations(deltaTime);
    // Zatrzymywanie postaci gdy dojdzie do krawedzi
    holdPlayerAtEdges();


    // Ruch w prawo
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::D)) {
        movingWithEqRight = true;
        movingWithEqLeft = false;
        //Skok podczas ruchu w prawo
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::W) && !isJumping) {
            verticalVelocity = JUMP_STRENGTH;
            isJumping = true;
        }

        if (canMoveRight) {
            this->playerSprite.move(characterSpeed * deltaTime, 0.0);
        }
        this->playerSprite.setTexture(this->rightTextures[this->animationIndex]);
        bulletDir = 1.0;
    }
    // Ruch w lewo
    else if (sf::Keyboard::isKeyPressed(sf::Keyboard::A)) {
        movingWithEqLeft = true;
        movingWithEqRight = false;
        //Skok podczas ruchu w lewo
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::W) && !isJumping) {
            verticalVelocity = JUMP_STRENGTH;
            isJumping = true;
        }

        if (canMoveLeft) {
            this->playerSprite.move(-characterSpeed * deltaTime, 0.0);
        }
        this->playerSprite.setTexture(this->leftTextures[this->animationIndex]);
        bulletDir = -1.0;
    }
    //Skok
    else if (sf::Keyboard::isKeyPressed(sf::Keyboard::W) && !isJumping) {
        verticalVelocity = JUMP_STRENGTH;
        isJumping = true;
        isOnGround = false;
    }

    else if (sf::Keyboard::isKeyPressed(sf::Keyboard::S)) {
        this->playerSprite.move(sf::Vector2f(0.0, characterSpeed * deltaTime));
    }

    //Strzaly
    if (this->shootCooldown > 0.0f) {
        this->shootCooldown -= deltaTime;
    }
    else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space)) {
        shoot();
        this->shootCooldown = this->shootCooldownMax;
    }

    if (event.type == sf::Event::KeyReleased) {
        if (event.key.code == sf::Keyboard::D) {
            this->playerSprite.setTexture(this->rightTextures[0]);
        }
        else if (event.key.code == sf::Keyboard::A) {
            this->playerSprite.setTexture(this->leftTextures[0]);
        }
    }

    // Dodawanie grawitacji, aby posta� wraca�a na ziemi�
    gravitation(deltaTime);

    updateEqPosition();

    //Akutalizacja pociskow
    for (auto it = bullets.begin(); it != bullets.end(); ) {
        it->update(deltaTime);
        if (it->isOffScreen()) {
            it = bullets.erase(it); // Usu� pocisk, je�li jest poza ekranem
        }
        else {
            ++it;
        }
    }

    // Je�li gracz nie jest na �adnej platformie, w��cz grawitacj�
    if (!isOnPlatform) {
        setOnGround(false);
    }

    if (isFalling) {
        float fallSpeed = 200.f;
        playerDeadSprite.move(0, fallSpeed * deltaTime);

        if (playerDeadSprite.getPosition().y >= 600) {
            isFalling = false;
            fallen = true;
        }
    }

    if (damageCooldown > 0) {
        damageCooldown -= deltaTime; // Zmniejsz cooldown
    }
}

void Player::render(sf::RenderTarget &target) {
    if (!isDead) {
        target.draw(this->playerSprite);
        for (const auto& eqItem : equippedItems) {
            target.draw(eqItem.sprite);
        }
    }
    else {
        target.draw(this->playerDeadSprite);
    }
        target.draw(this->ammoText);
        target.draw(this->amuSprite);
        for (auto& hp : hpSprite) {
            target.draw(hp);
        }

        for (auto& bullet : bullets) {
            bullet.render(&target);
        }
}


void Player::reduceHealth(int amount) {

    this->health -= amount;
    if(!hpSprite.empty())
        hpSprite.pop_back();

    if (this->health <= 0) {
        std::cout << "Gracz zginal! " << getCurrentHealth() << std::endl;
        // Implementacja zako�czenia gry
        setIsDead(true);
        isFalling = true;
        if (!isDeadSpriteSet) {
            textureManager.loadTexture("textury/smierc.png", "smierc");
            sf::Texture* smierc = textureManager.getTexture("smierc");
            if (smierc) {
                playerDeadSprite.setTexture(*smierc);
                playerDeadSprite.setPosition(getPlayerPosition().x, getPlayerPosition().y + 40);
            }
            else {
                std::cout << "Nie uda�o si� za�adowa� tekstury smiercii: " << "textury/smierc.png" << "\n";
            }
            isDeadSpriteSet = true;
        }
    }
}

void Player::incrementCurrentAmo() {
    currentAmmo++;
}

bool Player::getIsJumping() const {
    return this->isJumping;
}

std::vector<Bullet>& Player::getBullets() {
    return this->bullets;
}

float Player::getVerticalVelocity() const {
    return this->verticalVelocity;
}

int Player::getCurrentHealth() const {
    return this->health;
}

int Player::getCurrentAmo(){
    return currentAmmo;
}

// Zwiększanie doświadczenia
void Player::addExperience(int amount) {
    experience += amount;
    while (experience >= experienceToNext) {
        levelUp();
    }
}

// Awans na kolejny poziom
void Player::levelUp() {
    experience -= experienceToNext;
    level++;
    experienceToNext += 50 * level; // Skalowanie wymaganego doświadczenia

    // Tymczasowe zwiększenie statystyk (można dostosować)
    maxHealth += 10;
    damage += 2;
    characterSpeed += 10.f;

    std::cout << "Level up! Nowy poziom: " << level << std::endl;
    std::cout << "Nowe statystyki: zdrowie: " << maxHealth << ", obrażenia: " << damage << ", szybkość: " << characterSpeed << std::endl;
}

// Pobieranie aktualnych statystyk
int Player::getLevel() const { return level; }
int Player::getExperience() const { return experience; }
int Player::getExperienceToNext() const { return experienceToNext; }
int Player::getMaxHealth() const { return maxHealth; }
int Player::getDamage() const { return damage; }


