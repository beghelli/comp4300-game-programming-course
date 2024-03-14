#include <iostream>
#include <memory>
#include "Config.h"
#include "CTransform.h"
#include "Game.h"
#include "Entity.h"
#include "Vec2.h"

Game::Game(const Config& config)
	: m_config(config)
{}

int Game::run()
{
	Entity e("Player", 1);
	std::shared_ptr<CTransform> ct = std::make_shared<CTransform>();
	ct->pos = Vec2(1,1);
	e.cTransform = ct;

	e.cTransform->pos.print();
	return 1;
}
