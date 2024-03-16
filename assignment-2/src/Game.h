#pragma once
#include <iostream>
#include <SFML/Graphics/RenderWindow.hpp>
#include "EntityManager.h"
#include "SInput.h"
#include "SMovement.h"
#include "SRenderer.h"

class Game
{
	const Config& m_config;
	sf::RenderWindow m_window;
	EntityManager m_entities;
	SInput m_sInput;
	SMovement m_sMovement;
	SRenderer m_sRenderer;

	void runGameLoop();
	void createPlayer();

public:
	Game(const Config& configFile);
	int run();
};
