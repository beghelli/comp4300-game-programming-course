#include <iostream>
#include "Entity.h"

Entity::Entity(std::string tag, size_t id)
	: m_tag(tag)
	, m_id(id)
{}

size_t Entity::id() const
{
	return m_id;
}

std::string Entity::tag() const
{
	return m_tag;
}

bool Entity::isActive() const
{
	return m_active;
}
