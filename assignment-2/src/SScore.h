#pragma once
#include <SFML/Graphics/Text.hpp>
#include "EntityManager.h"

class SScore
{
	sf::Font m_font;
public:
	SScore();
	SScore(sf::Font font);
	void process(EntityManager& entities);
};
