#pragma once
#include <iostream>
#include <SFML/Graphics/RenderWindow.hpp>
#include "EntityManager.h"
#include "SEnemySpawner.h"
#include "SInput.h"
#include "SGun.h"
#include "SLifeSpan.h"
#include "SMovement.h"
#include "SRenderer.h"

class Game
{
	const Config& m_config;
	sf::RenderWindow m_window;
	EntityManager m_entities;
	SEnemySpawner m_sEnemySpawner;
	SInput m_sInput;
	SGun m_sGun;
	SLifeSpan m_sLifeSpan;
	SMovement m_sMovement;
	SRenderer m_sRenderer;
	unsigned int m_gameFrame { 0 };

	void runGameLoop();
	void createPlayer();
	void init();

public:
	Game(const Config& configFile);
	int run();
};
