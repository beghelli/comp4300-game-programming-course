#pragma once
#include "Vec2.h"

class CMouseInput
{
public:
	Vec2 pos;
	bool moved { false };
	Vec2 leftClickPos;
	bool leftClicked { false };
	Vec2 rightClickPos;
	bool rightClicked { false };
	CMouseInput();
};
