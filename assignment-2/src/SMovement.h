#pragma once
#include "EntityManager.h"
#include "Vec2.h"

class SMovement
{
	Vec2 m_movAreaSize;

	void applyMovementFromInput(std::shared_ptr<Entity>& e);
	void applyMovementFromMouseInput(std::shared_ptr<Entity>& e);
	double adaptVelocityToStayInsideMovArea(float pos, float limit, double velocity);
	double calculateMouseAngle(Vec2 ep, Vec2 mp);

public:
	SMovement();
	SMovement(Vec2 movAreaSize);
	void process(EntityManager& entities);
};
