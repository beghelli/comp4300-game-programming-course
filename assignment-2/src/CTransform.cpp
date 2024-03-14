#include "CTransform.h"

CTransform::CTransform() {};
CTransform::CTransform(Vec2& inpos, Vec2& invelocity, Vec2& inscale, double inangle)
	: pos(inpos)
	, velocity(invelocity)
	, scale(inscale)
	, angle(inangle)
{}

CTransform::~CTransform()
{}
