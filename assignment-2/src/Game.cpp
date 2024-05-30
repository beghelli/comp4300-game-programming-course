#include <iostream>
#include <memory>
#include <time.h>
#include <SFML/Graphics.hpp>
#include <SFML/Graphics/CircleShape.hpp>
#include <SFML/Graphics/Text.hpp>
#include <SFML/Window/Keyboard.hpp>
#include <SFML/Window/VideoMode.hpp>
#include "Config.h"
#include "CCollision.h"
#include "CEntityLife.h"
#include "CInput.h"
#include "CMouseInput.h"
#include "CGun.h"
#include "CScore.h"
#include "CShape.h"
#include "CShield.h"
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
	m_sEnemySpawner = SEnemySpawner(config.getEnemy(), wc.width, wc.height);
	m_sMovement = SMovement(Vec2(wc.width, wc.height));
	m_sGun = SGun(config.getBullet());

	sf::Font font;
	font.loadFromFile(config.getFont().font);
	m_sScore = SScore(font);
}

int Game::run()
{
	init();
	createPlayer();
	runGameLoop();

	return 1;
}

//
// Private methods.
//
void Game::init()
{
	std::srand(time(0));
}

void Game::runGameLoop()
{
	while (m_window.isOpen())
	{
		m_gameFrame++;
		m_entities.update();
		if (m_entities.getEntities("Player").size() == 0)
		{
			createPlayer();
		}
		m_sEnemySpawner.process(m_entities, m_gameFrame);
		m_sInput.process(m_entities, m_window);
		m_sGun.process(m_entities, m_gameFrame);
		m_sShield.process(m_entities);
		m_sMovement.process(m_entities);
		m_sCollisionDetector.process(m_entities);
		m_sEntityLife.process(m_entities);
		m_sScore.process(m_entities);
		m_sRenderer.process(m_entities, m_window);
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

	std::shared_ptr<CCollision> cc = std::make_shared<CCollision>();
	cc->collisionRadius = pc.radius;
	cc->checkAgainstTags.push_back("Enemy");
	e->cCollision = cc;

	std::shared_ptr<CScore> csc = std::make_shared<CScore>();
	e->cScore = csc;

	std::shared_ptr<CShield> cShield = std::make_shared<CShield>(480, 480, 2, 1);
	e->cShield = cShield;

	std::vector<std::string> tags {"Enemy"};
	std::shared_ptr<CEntityLife> cLife = std::make_shared<CEntityLife>(tags);
	e->cEntityLife = cLife;
}
