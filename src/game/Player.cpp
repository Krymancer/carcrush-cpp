#include <game/Player.hpp>

Player::Player() {
    this->x = 96;
    this->y = 540;
}

Player::~Player() {
    //TODO
}

bool Player::init() {
    /* Can't load in the constructor because needed a global scope
    * When the variable was created SDL_Init has not yet called
    * Causing in not having a renderer to make the texture
    */
    return this->mTexture.loadFromFile("./assets/png/blue.png");
}

void Player::show() {
    this->mTexture.draw(this->x, this->y);
}

void Player::update() {
    //TODO
}

void Player::move(int direction) {
    // Bounders
    if (this->x == 18 && direction == this->LETF) { //18 is the minimum valid x value
        return;
    } else if (this->x == 252 && direction == this->RIGHT) { //252 is the maximum valid x value
        return;
    }

    if (direction == this->LETF) {
        this->x -= this->offset;
    } else if (direction == this->RIGHT) {
        this->x += this->offset;
    }
}