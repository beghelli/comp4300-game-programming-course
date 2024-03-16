#pragma once
#include "EntityManager.h"
#include "Vec2.h"

class SMovement
{
	Vec2 m_movAreaSize;

public:
	SMovement();
	SMovement(Vec2 movAreaSize);
	void process(EntityManager& entities);
	void applyMovementFromInput(std::shared_ptr<Entity>& e);
	double adaptVelocityToStayInsideMovArea(float pos, float limit, double velocity);
};
