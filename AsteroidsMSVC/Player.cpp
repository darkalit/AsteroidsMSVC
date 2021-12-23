#include "Player.h"

// Constructor
Player::Player(float x, float y) {
    this->setPos                    (x, y);

    this->initVars                  ();
    this->initShape                 ();
}

Player::~Player() {

}

// Initialize some variables
void Player::initVars() {
    this->angle                     = 0.f;
    this->acceleration              = 3.f;
    this->speed                     = 0.1f;
    this->direction                 = sf::Vector2f(0.f, 0.f);
    this->aCooldownMax              = 10.f;
    this->aCooldown                 = this->aCooldownMax;
}

// Initialize the player's body
void Player::initShape() {
    this->body.setFillColor         (sf::Color::Transparent);
    this->body.setOutlineColor      (sf::Color::White);
    this->body.setOutlineThickness  (2.0f);
    this->body.setRadius            (15.0f);
    this->body.setPointCount        (3);
    this->body.setScale             (1, 1.5);
    this->body.setOrigin            (3 * this->body.getRadius() / (2 * sqrtf(3)), 
                                     3 * this->body.getRadius() / (2 * sqrtf(3)));
    this->body.setRotation          (0.f);
}

// Keyboard input
void Player::updateInput() {
    // Left
    if (sf::Keyboard::isKeyPressed  (sf::Keyboard::Left)) {
        this->body.setRotation      (angle -= 5.f);
    }

    // Right
    else 
    if (sf::Keyboard::isKeyPressed  (sf::Keyboard::Right)) {
        this->body.setRotation      (angle += 5.f);
    }

    // Forward:Accelerate (in direction of vector)
    if (sf::Keyboard::isKeyPressed  (sf::Keyboard::Up)) {
        this->direction.x           +=  sinf(M_PI * this->angle / 180) * this->acceleration;
        this->direction.y           += -cosf(M_PI * this->angle / 180) * this->acceleration;
    }

    // Slowing the spaceship
    if (!sf::Keyboard::isKeyPressed (sf::Keyboard::Up)) {
        if (vecLen(this->direction) > 0.f) {
            this->direction.x       *= 0.98f;
            this->direction.y       *= 0.98f;
        }
        if (vecLen(this->direction) < 2.f) {
            this->direction.x       = 0;
            this->direction.y       = 0;
        }
    }

    // Max speed limit
    if (vecLen(this->direction) >= powf(100.f, 2)) {
        this->direction.x           -=  sinf(M_PI * this->angle / 180) * this->acceleration;
        this->direction.y           -= -cosf(M_PI * this->angle / 180) * this->acceleration;
    }

    // Moving the spaceship
    this->redirection               += this->direction * this->speed;
    this->setPos                    (this->redirection.x, this->redirection.y);
}

// Update player's stuff
void Player::update() {
    this->updateInput               ();
}

// Render player
void Player::render(sf::RenderTarget* target) {
    target->draw                    (this->body);
}

// Set position of player
void Player::setPos(float x, float y) {
    this->body.setPosition          (x - this->body.getRadius(), y);

    this->redirection               = sf::Vector2f(x, y);
}

// Get position of player as 2d vector
sf::Vector2f Player::getPos() {
    sf::Vector2f    vector          = this->body.getPosition();
    return          vector;
}

// Rotate player
void Player::Rotate(float angle) {
    this->body.setRotation          (angle);
}

//void Player::setDirection(sf::Vector2f vector) {
//    this->direction = vector;
//}

// Get vector of player's direction
sf::Vector2f Player::getDirection() {
    sf::Vector2f     direction_;
    direction_.x                    = cosf((this->body.getRotation() - 90.f) * M_PI / 180);
    direction_.y                    = sinf((this->body.getRotation() - 90.f) * M_PI / 180);
    direction_                      = normV(direction_);
    return           direction_;
}

const sf::FloatRect Player::getBounds() const
{
    return this->body.getGlobalBounds();
}
