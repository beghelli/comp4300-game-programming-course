#pragma once

class CLifeSpan
{
public:
	CLifeSpan();
	CLifeSpan(unsigned int inlifeSpan);
	unsigned int lifeSpan;
	unsigned int ageInFrames {0};
};
