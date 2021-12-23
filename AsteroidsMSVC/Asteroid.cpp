#include "Asteroid.h"

Asteroid::Asteroid()
{
}

Asteroid::Asteroid(sf::Texture& texture, float scale, sf::Vector2f pos, sf::Vector2f direction, float speed)
{
	this->shape.setTexture(texture);
	this->shape.setScale(scale, scale);
	this->shape.setPosition(pos);
	this->shape.setOrigin(this->shape.getGlobalBounds().width*2, this->shape.getGlobalBounds().height*2);
	this->direction = direction;
	this->speed = speed;
}

Asteroid::~Asteroid()
{
}

sf::Vector2f Asteroid::getPos()
{
	return this->shape.getPosition();
}

void Asteroid::setPos(float x, float y)
{
	// idk why I put -20.f to x
	this->shape.setPosition(x-20.f, y);
}

void Asteroid::Rotate(float angle)
{
	this->shape.setRotation(angle);
}

sf::Vector2f Asteroid::getDirection()
{
	return this->direction;
}

const sf::FloatRect Asteroid::getBounds() const
{
	return this->shape.getGlobalBounds();
}

void Asteroid::update()
{
	this->shape.move(this->direction * this->speed);
}

void Asteroid::render(sf::RenderTarget* target)
{
	target->draw(this->shape);
}
