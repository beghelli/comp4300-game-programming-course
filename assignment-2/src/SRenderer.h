#pragma once
#include <SFML/Graphics/RenderWindow.hpp>
#include "EntityManager.h"

class SRenderer
{

public:
	SRenderer();
	void process(EntityManager& entities, sf::RenderWindow& window);
};
