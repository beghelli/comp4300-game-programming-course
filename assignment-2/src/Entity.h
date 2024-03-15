#pragma once
#include <iostream>
#include <memory>
#include "CTransform.h"
#include "CShape.h"

class Entity
{
	std::string m_tag;
	bool m_active;
	size_t m_id;
public:
	std::shared_ptr<CTransform> cTransform;
	std::shared_ptr<CShape> cShape;

	Entity(std::string tag, size_t id);
	size_t id() const;
	std::string tag() const;
	bool isActive() const;
};
