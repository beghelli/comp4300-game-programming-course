#pragma once
#include <iostream>
#include <memory>
#include <vector>
#include <map>
#include "Entity.h"

class EntityManager
{
	typedef std::vector<std::shared_ptr<Entity>> VEntities;
	std::map<std::string, VEntities> m_entitiesByTag;
	VEntities m_entities;
	VEntities m_entitiesToAdd;
	size_t entitiesCount {0};

public:
	EntityManager();
	void update();
	std::shared_ptr<Entity> addEntity(std::string tag);
	VEntities&getEntities();
	VEntities& getEntities(std::string tag);
};
