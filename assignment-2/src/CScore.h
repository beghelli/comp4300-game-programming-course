#pragma once
#include <SFML/Graphics/Text.hpp>

class CScore
{
public:
	unsigned int score {0};
	sf::Text scoreText;
	CScore();
};
