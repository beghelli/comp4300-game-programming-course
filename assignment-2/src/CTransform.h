#pragma once
#include "Vec2.h"

class CTransform
{
public:
	Vec2 pos;
	Vec2 velocity;
	Vec2 scale;
	double angle;
	double maxVelocity;
	double rotationVelocity {0};

	CTransform();
	CTransform(Vec2 pos, Vec2 velocity, Vec2 scale, double angle, double maxVelocity);
	~CTransform();
};
