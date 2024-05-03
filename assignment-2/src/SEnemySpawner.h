#pragma once

#include "Config.h"
#include "EntityManager.h"

class SEnemySpawner
{

private:
	Config::EnemyCfg m_enemyCfg;
	unsigned int m_lastEnemyAddedFrame { 1 };

public:
	SEnemySpawner();
	SEnemySpawner(Config::EnemyCfg enemyCfg);
	void process(EntityManager& entities, unsigned int gameFrame);
};
