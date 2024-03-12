#include <iostream>
#include "Config.h"
#include "Game.h"

Game::Game(const Config& config)
	: m_config(config)
{}

int Game::run()
{
	return 1;
}
