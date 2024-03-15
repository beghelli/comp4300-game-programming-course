#pragma once
#include <SFML/Graphics/CircleShape.hpp>

class CShape
{
public:
	sf::CircleShape shape;
	CShape();
	CShape(sf::CircleShape& inshape);
};
