#pragma once
#include <iostream>
#include <SFML/Graphics/RenderWindow.hpp>
#include "EntityManager.h"

class Game
{
	const Config& m_config;
	sf::RenderWindow m_window;
	EntityManager m_entities;

	void runGameLoop();
	void runInputSystem();
	void runRendererSystem();

public:
	Game(const Config& configFile);
	int run();
};
