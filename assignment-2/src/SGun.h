#pragma once
#include "EntityManager.h"
#include "Config.h"

class SGun
{
	Config::BulletCfg m_bulletCfg;
	void handleFire(EntityManager& entities, std::shared_ptr<Entity>& e, unsigned int gameFrame);
public:
	SGun();
	SGun(Config::BulletCfg bulletCfg);

	void process(EntityManager& entities, unsigned int gameFrame);
};
