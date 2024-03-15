#include <iostream>
#include <memory>
#include <SFML/Graphics.hpp>
#include <SFML/Graphics/CircleShape.hpp>
#include <SFML/Window/VideoMode.hpp>
#include "Config.h"
#include "CShape.h"
#include "CTransform.h"
#include "Entity.h"
#include "EntityManager.h"
#include "Game.h"
#include "Vec2.h"

Game::Game(const Config& config)
	: m_config(config)
{
	Config::WindowCfg wc = config.getWindow();
	sf::VideoMode vm(wc.width, wc.height);
	m_window.create(vm, "My Game");
	m_window.setFramerateLimit(wc.frameRate);
}

int Game::run()
{
	std::shared_ptr<Entity> e = m_entities.addEntity("Player", 1);
	std::shared_ptr<CTransform> ct = std::make_shared<CTransform>();
	ct->pos = Vec2(1,1);
	e->cTransform = ct;

	Config::PlayerCfg pc = m_config.getPlayer();
	sf::CircleShape shape(pc.radius, pc.shapeVertices);
	shape.setFillColor(pc.fillColor);
	shape.setOutlineColor(pc.outlineColor);
	shape.setOutlineThickness(pc.outlineThickness);
	std::shared_ptr<CShape> cs = std::make_shared<CShape>(shape);
	e->cShape = cs;

	runGameLoop();

	return 1;
}

void Game::runGameLoop()
{
	while (m_window.isOpen())
	{
		m_entities.update();
		runInputSystem();
		runRendererSystem();
	}
}

void Game::runInputSystem()
{
	sf::Event event;
	while (m_window.pollEvent(event))
	{
		if (event.type == sf::Event::Closed)
		{
			m_window.close();
		}
	}
}

void Game::runRendererSystem()
{
	m_window.clear();
	for (std::shared_ptr<Entity>& e : m_entities.getEntities())
	{
		sf::Shape& shape = e->cShape->shape;
		m_window.draw(shape);
	}
	m_window.display();
}
