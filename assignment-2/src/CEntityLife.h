#pragma once

#include <iostream>

class CEntityLife
{

public:
	std::vector<std::string> m_dieOnCollidingWithTags;

	CEntityLife(std::vector<std::string> dieOnCollidingWithTags);

};
