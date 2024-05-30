#pragma once

#include "Entity.h"
#include "EntityManager.h"

class SShield
{
public:
	SShield();
	void process(EntityManager& entities);
	void handleShield(std::shared_ptr<Entity>& e, EntityManager& entities);
	void createShield(std::shared_ptr<Entity>& e, EntityManager& entities);
};
