#include <vector>
#include "CEntityLife.h"

CEntityLife::CEntityLife(std::vector<std::string> dieOnCollidingWithTags)
	: m_dieOnCollidingWithTags(dieOnCollidingWithTags) {}
