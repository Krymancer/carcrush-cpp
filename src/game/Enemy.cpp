#include <game/Enemy.hpp>
#include <random>

Enemy::Enemy() {
    setStartPosition();
}

Enemy::~Enemy() {
}

int Enemy::getX() {
    return this->x;
}

int Enemy::getY() {
    return this->y;
}

int Enemy::getWidth() {
    return this->mTexture.getWidth();
}

int Enemy::getHeight() {
    return this->mTexture.getHeight();
}

bool Enemy::init(int id) {
    // Debug purpouses to know graphically the enemies
    if (id == 0)
        return this->mTexture.loadFromFile("./assets/png/green.png");
    else if (id == 1)
        return this->mTexture.loadFromFile("./assets/png/gray.png");
    else
        return this->mTexture.loadFromFile("./assets/png/pink.png");
}

void Enemy::update() {
    this->y += this->speed;

    if (this->y > Engine::SCREEN_HEIGHT) { // Offscreen
        this->setStartPosition(); // "Generates again"
    }

    //TODO
}

void Enemy::show() {
    this->mTexture.draw(this->x, this->y, 0, nullptr, nullptr, SDL_FLIP_VERTICAL);
}

void Enemy::setStartPosition() {
    this->y = -138; // 138 is the height of the sprite

    std::random_device dev;
    std::mt19937 rng(dev());

    std::uniform_int_distribution<std::mt19937::result_type> dist4(0, 3);
    std::uniform_int_distribution<std::mt19937::result_type> dist200(100, 600);

    int startPosition = dist4(rng);  //Chose one of the 4 start position

    this->x = this->startPositions[startPosition];
    this->y -= dist200(rng);
}