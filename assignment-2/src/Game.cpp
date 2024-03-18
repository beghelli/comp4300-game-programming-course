#include <iostream>
#include <memory>
#include <SFML/Graphics.hpp>
#include <SFML/Graphics/CircleShape.hpp>
#include <SFML/Window/Keyboard.hpp>
#include <SFML/Window/VideoMode.hpp>
#include "Config.h"
#include "CInput.h"
#include "CMouseInput.h"
#include "CGun.h"
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
	m_sMovement = SMovement(Vec2(wc.width, wc.height));
	m_sGun = SGun(config.getBullet());
}

int Game::run()
{
	createPlayer();
	runGameLoop();

	return 1;
}

//
// Private methods.
//
void Game::runGameLoop()
{
	while (m_window.isOpen())
	{
		m_gameFrame++;
		m_entities.update();
		m_sInput.process(m_entities, m_window);
		m_sMovement.process(m_entities);
		m_sRenderer.process(m_entities, m_window);
		m_sGun.process(m_entities, m_gameFrame);
	}
}

void Game::createPlayer()
{
	Config::PlayerCfg pc = m_config.getPlayer();
	std::shared_ptr<Entity> e = m_entities.addEntity("Player");
	std::shared_ptr<CTransform> ct = std::make_shared<CTransform>();
	ct->pos = Vec2(m_config.getWindow().width / 2, m_config.getWindow().height / 2);
	ct->velocity = Vec2(0,0);
	ct->maxVelocity = pc.velocity;
	e->cTransform = ct;

	sf::CircleShape shape(pc.radius, pc.shapeVertices);
	shape.setOrigin(pc.radius, pc.radius);
	shape.setFillColor(pc.fillColor);
	shape.setOutlineColor(pc.outlineColor);
	shape.setOutlineThickness(pc.outlineThickness);
	std::shared_ptr<CShape> cs = std::make_shared<CShape>(shape);
	e->cShape = cs;

	std::shared_ptr<CInput> ci = std::make_shared<CInput>();
	e->cInput = ci;

	std::shared_ptr<CMouseInput> cmi = std::make_shared<CMouseInput>();
	e->cMouseInput = cmi;

	std::shared_ptr<CGun> cgun = std::make_shared<CGun>();
	cgun->framesPerFire = pc.fireRate;
	e->cGun = cgun;
}
