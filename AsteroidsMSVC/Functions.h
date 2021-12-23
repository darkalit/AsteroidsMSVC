#ifndef ASTEROIDSMSVC_FUNCTIONS_H
#define ASTEROIDSMSVC_FUNCTIONS_H

#include "SFML/System.hpp"

// Reverse square root (thx ID software)
float			Q_rsqrt		(float number);

// SFML Vector lenth
float			vecLen		(sf::Vector2f vector);

// Normalize SFML vector
sf::Vector2f	normV		(sf::Vector2f vector);

#endif
