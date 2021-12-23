#ifndef ASTEROIDSMSVC_OBJECT_H
#define ASTEROIDSMSVC_OBJECT_H

#include "Functions.h"

#include "SFML/Window.hpp"
#include "SFML/Graphics.hpp"
#include "SFML/System.hpp"
#include "SFML/Audio.hpp"

class Object {
protected:

	float speed;
	float angle;

public:
	// Constructor/Destructor;
							Object			();
	virtual					~Object			();

	// Position functions;
	virtual sf::Vector2f	getPos			()							= 0;
	virtual void			setPos			(float x=0, float y=0)		= 0;

	// Move object to the opposite screen side when crossing another side;
	virtual void			screenMove		(sf::VideoMode videoMode);

	// Angle and rotation manipulation;
	virtual float			getAngle		();
	virtual void			setAngle		(float angle);
	virtual void			Rotate			(float angle)				= 0;

	// Get direction vector of moving object;
	virtual sf::Vector2f	getDirection	()							= 0;
	virtual const sf::FloatRect     getBounds()                   const = 0;

	// Update state of object and render it; 
	virtual void			update			()							= 0;
	virtual void			render			(sf::RenderTarget* target)	= 0;
};


#endif