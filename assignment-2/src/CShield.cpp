#include "CShield.h"

CShield::CShield() {}

CShield::CShield(unsigned int maxEnergy, unsigned int energy, unsigned int consumptionPerFrame, unsigned int regenPerFrame)
	: m_maxEnergy(maxEnergy)
	, m_energy(energy)
	, m_consumptionPerFrame(consumptionPerFrame)
	, m_regenPerFrame(regenPerFrame) {}
