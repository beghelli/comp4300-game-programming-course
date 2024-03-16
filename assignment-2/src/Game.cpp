#include <iostream>
#include <memory>
#include <SFML/Graphics.hpp>
#include <SFML/Graphics/CircleShape.hpp>
#include <SFML/Window/Keyboard.hpp>
#include <SFML/Window/VideoMode.hpp>
#include "Config.h"
#include "CInput.h"
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
	Config::PlayerCfg pc = m_config.getPlayer();
	std::shared_ptr<Entity> e = m_entities.addEntity("Player", 1);
	std::shared_ptr<CTransform> ct = std::make_shared<CTransform>();
	ct->pos = Vec2(1,1);
	ct->velocity = Vec2(pc.velocity, pc.velocity);
	e->cTransform = ct;

	sf::CircleShape shape(pc.radius, pc.shapeVertices);
	shape.setFillColor(pc.fillColor);
	shape.setOutlineColor(pc.outlineColor);
	shape.setOutlineThickness(pc.outlineThickness);
	std::shared_ptr<CShape> cs = std::make_shared<CShape>(shape);
	e->cShape = cs;

	std::shared_ptr<CInput> ci = std::make_shared<CInput>();
	e->cInput = ci;

	runGameLoop();

	return 1;
}

void Game::runGameLoop()
{
	while (m_window.isOpen())
	{
		m_window.clear();
		m_entities.update();
		for (std::shared_ptr<Entity>& e : m_entities.getEntities())
		{
			runInputSystem(e);
			runMovementSystem(e);
			runRendererSystem(e);
		}
		m_window.display();
	}
}

void Game::runInputSystem(std::shared_ptr<Entity>& e)
{
	sf::Event event;
	while (m_window.pollEvent(event))
	{
		if (event.type == sf::Event::Closed)
		{
			m_window.close();
		}
		else if (event.type == sf::Event::KeyPressed)
		{
			if (e->cInput)
			{
				if (event.key.code == sf::Keyboard::Key::D)
				{
					e->cInput->right = true;
				}
			}
		}
		else if (event.type == sf::Event::KeyReleased)
		{
			if (e->cInput)
			{
				if (event.key.code == sf::Keyboard::Key::D)
				{
					e->cInput->right = false;
				}
			}
		}
	}
}

void Game::runMovementSystem(std::shared_ptr<Entity>& e)
{
	if (e->cTransform && e->cShape)
	{
		sf::Shape& shape = e->cShape->shape;
		if (e->cInput)
		{
			if (e->cInput->right)
			{
				e->cTransform->pos.x += e->cTransform->velocity.x;
			}
		}
		shape.setPosition(e->cTransform->pos.x, e->cTransform->pos.y);
	}
}

void Game::runRendererSystem(std::shared_ptr<Entity>& e)
{
	if (e->cShape)
	{
		sf::Shape& shape = e->cShape->shape;
		m_window.draw(shape);
	}
}
