#include <iostream>
#include "Game.h"

Game::Game(const std::string& configFile)
	: m_configFile(configFile)
{}

int Game::run()
{
	std::cout << "Game ran. Config file was: " << m_configFile << std::endl;
	return 1;
}
