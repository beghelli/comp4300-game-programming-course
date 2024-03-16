#pragma once
#include <SFML/Graphics/RenderWindow.hpp>
#include "EntityManager.h"

class SInput
{
	void handleForEntity(sf::Event event, std::shared_ptr<Entity>& e);

public:
	SInput();
	void process(EntityManager& entities, sf::RenderWindow& window);
};
