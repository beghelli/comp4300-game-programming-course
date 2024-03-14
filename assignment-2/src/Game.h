#pragma once
#include <iostream>

class Game
{
	const Config& m_config;

public:
	Game(const Config& configFile);
	int run();
};
