#pragma once

#include <iostream>
#include <vector>

class CCollision
{

public:
	std::vector<std::string> checkAgainstTags;
	unsigned int collisionRadius;
	bool collided {false};
	CCollision();
};
