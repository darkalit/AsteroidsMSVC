#include "Object.h"

Object::Object()
{
}

Object::~Object()
{
}

void Object::screenMove(sf::VideoMode videoMode)
{
    if (this->getPos().x > (float)videoMode.width)
        this->setPos    (((float)sf::VideoMode::getDesktopMode().width) / 95, this->getPos().y);

    if (this->getPos().y > (float)videoMode.height)
        this->setPos    (this->getPos().x, 0);

    if (this->getPos().x < 0)
        this->setPos    ((float)videoMode.width, this->getPos().y);

    if (this->getPos().y < 0)
        this->setPos    (this->getPos().x, (float)videoMode.height);
}

float Object::getAngle()
{
	return              angle;
}

void Object::setAngle(float angle)
{
    this->angle         = angle;
}
