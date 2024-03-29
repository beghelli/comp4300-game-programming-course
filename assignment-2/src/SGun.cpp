#include <SFML/Graphics/CircleShape.hpp>
#include <cmath>
#include "SGun.h"
#include "CShape.h"
#include "CTransform.h"
#include "Vec2.h"

SGun::SGun() {}
SGun::SGun(Config::BulletCfg bulletCfg)
	: m_bulletCfg(bulletCfg)
{}

void SGun::process(EntityManager& entities, unsigned int gameFrame)
{
	for (auto& e : entities.getEntities())
	{
		if (e->cGun && e->cMouseInput && e->cTransform)
		{
			handleFire(entities, e, gameFrame);
		}
	}
}

void SGun::handleFire(EntityManager& entities, std::shared_ptr<Entity>& e, unsigned int gameFrame)
{
	if (e->cMouseInput->leftClicked && (gameFrame - e->cGun->lastFireFrame) > e->cGun->framesPerFire)
	{
		std::shared_ptr<Entity> bullet = entities.addEntity("Bullet");
		sf::CircleShape cs(m_bulletCfg.radius, m_bulletCfg.shapeVertices);
		cs.setFillColor(m_bulletCfg.fillColor);
		cs.setOutlineColor(m_bulletCfg.outlineColor);
		cs.setOutlineThickness(m_bulletCfg.outlineThickness);
		std::shared_ptr<CShape> compS = std::make_shared<CShape>(cs);
		bullet->cShape = compS;

		std::shared_ptr<CTransform> ct = std::make_shared<CTransform>(
			e->cTransform->pos,
			Vec2(m_bulletCfg.velocity, m_bulletCfg.velocity),
			Vec2(0,0),
			e->cTransform->angle,
			m_bulletCfg.velocity
		);
		bullet->cTransform = ct;

		e->cGun->lastFireFrame = gameFrame;
	}
}
