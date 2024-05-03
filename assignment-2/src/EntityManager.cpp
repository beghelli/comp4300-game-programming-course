#include "EntityManager.h"
#include "Entity.h"

EntityManager::EntityManager() {};

void EntityManager::update()
{
	for (std::shared_ptr<Entity>& e : m_entitiesToAdd)
	{
		m_entities.push_back(e);
		m_entitiesByTag[e->tag()].push_back(e);
	}

	std::vector<int> toDelete;
	unsigned int counter = 0;
	for (std::shared_ptr<Entity>& e : m_entities)
	{
		if (! e->isActive())
		{
			toDelete.push_back(counter);
		}
		counter++;
	}

	for (int index : toDelete)
	{
		m_entities.erase(m_entities.begin() + index);
	}

	toDelete.clear();
	m_entitiesToAdd.clear();
}

std::shared_ptr<Entity> EntityManager::addEntity(std::string tag)
{
	std::shared_ptr<Entity> e = std::make_shared<Entity>(tag, entitiesCount++);
	m_entitiesToAdd.push_back(e);

	return e;
}

EntityManager::VEntities& EntityManager::getEntities()
{
	return m_entities;
}

EntityManager::VEntities& EntityManager::getEntities(std::string tag)
{
	return m_entitiesByTag[tag];
}


