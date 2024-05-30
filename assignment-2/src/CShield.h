#pragma once

class CShield
{

public:
	unsigned int m_maxEnergy { 0 };
	unsigned int m_energy { 0 };
	unsigned int m_consumptionPerFrame { 0 };
	unsigned int m_regenPerFrame { 0 };
	bool m_enabled { false };

	CShield();
	CShield(unsigned int maxEnergy, unsigned int energy, unsigned int consumptionPerFrame, unsigned int regenPerFrame);
};
