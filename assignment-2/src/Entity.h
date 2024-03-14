#pragma once
#include <iostream>
#include <memory>
#include "CTransform.h"

class Entity
{
	std::string m_tag;
	bool m_active;
	size_t m_id;
public:
	std::shared_ptr<CTransform> cTransform;

	Entity(std::string tag, size_t id);
	size_t id() const;
	std::string tag() const;
	bool isActive() const;
};
