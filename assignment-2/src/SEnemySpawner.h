#pragma once

#include "Config.h"
#include "EntityManager.h"

class SEnemySpawner
{

private:
	struct WindowLimits
	{
		unsigned int left;
		unsigned int right;
		unsigned int top;
		unsigned int bottom;
	};

	Config::EnemyCfg m_enemyCfg;
	unsigned int m_lastEnemyAddedFrame { 1 };
	WindowLimits m_enemySpawnWindowLimits;

public:
	SEnemySpawner();
	SEnemySpawner(
			Config::EnemyCfg enemyCfg,
			unsigned int windowWidth,
			unsigned int windowHeight);
	void process(
			EntityManager& entities,
			unsigned int gameFrame);
};
