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
    if (this->x == 18 && direction == this->LETF) {  //18 is the minimum valid x value
        return;
    } else if (this->x == 252 && direction == this->RIGHT) {  //252 is the maximum valid x value
        return;
    }

    if (direction == this->LETF) {
        this->x -= this->offset;
    } else if (direction == this->RIGHT) {
        this->x += this->offset;
    }
}

bool Player::collide(Enemy &enemy) {
    // Define the limits
    enum collider { LEFT,
                    RIGHT,
                    TOP,
                    BOTTOM };

    int collidderPlayer[4];
    int colliderEnemy[4];

    collidderPlayer[collider::LEFT] = this->x;
    collidderPlayer[collider::RIGHT] = this->x + this->mTexture.getWidth();
    collidderPlayer[collider::TOP] = this->y;
    collidderPlayer[collider::BOTTOM] = this->y + this->mTexture.getHeight();

    colliderEnemy[collider::LEFT] = enemy.getX();
    colliderEnemy[collider::RIGHT] = enemy.getX() + enemy.getWidth();
    colliderEnemy[collider::TOP] = enemy.getY();
    colliderEnemy[collider::BOTTOM] = enemy.getY() + enemy.getHeight();

    // Debug

    std::cout << "collider Player " << std::endl
              << "  LEFT: " << collidderPlayer[collider::LEFT] << std::endl
              << "  RIGHT: " << collidderPlayer[collider::RIGHT] << std::endl
              << "  TOP: " << collidderPlayer[collider::TOP] << std::endl
              << "  BOTTOM: " << collidderPlayer[collider::BOTTOM] << std::endl;

    std::cout << "collider Enemy " << std::endl
              << "  LEFT: " << colliderEnemy[collider::LEFT] << std::endl
              << "  RIGHT: " << colliderEnemy[collider::RIGHT] << std::endl
              << "  TOP: " << colliderEnemy[collider::TOP] << std::endl
              << "  BOTTOM: " << colliderEnemy[collider::BOTTOM] << std::endl;

    std::cout << std::endl;

    if (collidderPlayer[collider::LEFT] != colliderEnemy[collider::LEFT]) {
        return false;
    } else if (collidderPlayer[collider::TOP] <= colliderEnemy[collider::BOTTOM]) {
        if (collidderPlayer[collider::BOTTOM] >= colliderEnemy[collider::TOP]) {
            std::cout << "hit" << std::endl; // Debug
            return true;
        }
    }


return false;
}