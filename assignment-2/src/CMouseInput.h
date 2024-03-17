#pragma once
#include "Vec2.h"

class CMouseInput
{
public:
	Vec2 pos;
	bool moved { false };
	CMouseInput();
};
