#pragma once

#include "EntityManager.h"

class SCollisionDetector
{

public:
	SCollisionDetector();
	void process(EntityManager& entities);
};
