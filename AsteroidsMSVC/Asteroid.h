#ifndef ASTEROIDS_ASTEROID_H
#define ASTEROIDS_ASTEROID_H

#include "Object.h"

class Asteroid : public Object
{
private:
	sf::Sprite shape;

	sf::Vector2f direction;

public:
	// Constructor/Destructor;
							Asteroid();
							Asteroid(sf::Texture& texture,
									 float scale,
									 sf::Vector2f pos,
									 sf::Vector2f direction,
									 float speed);
	virtual					~Asteroid();

	// Position functions;
	sf::Vector2f			getPos()									override;
	void					setPos(float x = 0, float y = 0)			override;

	// Move object to the opposite screen side when crossing another side;
	//void					screenMove(sf::VideoMode videoMode)			override;

	// Angle and rotation manipulation;
	void					Rotate(float angle)							override;

	// Get direction vector of moving object;
	sf::Vector2f			getDirection()								override;
	const sf::FloatRect     getBounds()							  const override;

	// Update state of object and render it; 
	void					update()									override;
	void					render(sf::RenderTarget* target)			override;
};
#endif ASTEROIDS_ASTEROID_H
