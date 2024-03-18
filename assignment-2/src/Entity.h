#pragma once
#include <iostream>
#include <memory>
#include "CInput.h"
#include "CGun.h"
#include "CMouseInput.h"
#include "CShape.h"
#include "CTransform.h"

class Entity
{
	std::string m_tag;
	bool m_active;
	size_t m_id;
public:
	std::shared_ptr<CTransform> cTransform;
	std::shared_ptr<CShape> cShape;
	std::shared_ptr<CInput> cInput;
	std::shared_ptr<CMouseInput> cMouseInput;
	std::shared_ptr<CGun> cGun;

	Entity(std::string tag, size_t id);
	size_t id() const;
	std::string tag() const;
	bool isActive() const;
};
