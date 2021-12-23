#include "Bullet.h"

Bullet::Bullet() {
    this->initVars();
}

Bullet::Bullet(sf::CircleShape* shape, sf::Vector2f pos, sf::Vector2f direction, float speed) {
    this->shape                 = *shape;
    this->shape.setPosition      (pos);
    this->direction             = direction;
    this->speed                 = speed;
    this->initVars();
}

Bullet::~Bullet() {

}

void Bullet::setLifeTime(float lifeTime)
{
    this->lifeTime = lifeTime;
}

float Bullet::getLifeTime()
{
    return this->lifeTime;
}

void Bullet::initVars()
{
    this->lifeTime = 10.f;
}

sf::Vector2f Bullet::getPos()
{
    return this->shape.getPosition();
}

void Bullet::setPos(float x, float y)
{
    this->shape.setPosition(x, y);
}

void Bullet::Rotate(float angle)
{
}

sf::Vector2f Bullet::getDirection()
{
    return sf::Vector2f();
}

const sf::FloatRect Bullet::getBounds() const {
    return this->shape.getGlobalBounds();
}

void Bullet::update() {
    this->shape.move            (this->speed * this->direction);
}

void Bullet::render(sf::RenderTarget* target) {
    target->draw                (this->shape);
}
