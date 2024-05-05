#include "CTransform.h"

CTransform::CTransform() {};
CTransform::CTransform(Vec2 inpos, Vec2 invelocity, Vec2 inscale, double inangle, double inmaxVelocity)
	: pos(inpos)
	, velocity(invelocity)
	, scale(inscale)
	, angle(inangle)
	, maxVelocity(inmaxVelocity) {}

CTransform::~CTransform() {}
