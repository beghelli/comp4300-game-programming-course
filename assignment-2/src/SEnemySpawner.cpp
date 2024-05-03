#include "SEnemySpawner.h"
#include "Entity.h"
#include "CTransform.h"
#include "CShape.h"

SEnemySpawner::SEnemySpawner() {}

SEnemySpawner::SEnemySpawner(Config::EnemyCfg enemyCfg)
	: m_enemyCfg(enemyCfg) {}

void SEnemySpawner::process(EntityManager& entities, unsigned int gameFrame)
{
	unsigned int diffSinceLastAddition = gameFrame - m_lastEnemyAddedFrame;
	if (diffSinceLastAddition == 0 || diffSinceLastAddition == m_enemyCfg.spawnInterval)
	{
		std::shared_ptr<Entity> enemy = entities.addEntity("Enemy");
		std::shared_ptr<CTransform> ct = std::make_shared<CTransform>();
		ct->pos = Vec2(20, 20);
		ct->velocity = Vec2(m_enemyCfg.velocity.max,m_enemyCfg.velocity.max);
		enemy->cTransform = ct;

		sf::CircleShape shape(m_enemyCfg.radius, m_enemyCfg.vertices.max);
		shape.setOrigin(m_enemyCfg.radius, m_enemyCfg.radius);
		shape.setOutlineColor(m_enemyCfg.outlineColor);
		shape.setOutlineThickness(m_enemyCfg.outlineThickness);
		std::shared_ptr<CShape> cs = std::make_shared<CShape>(shape);
		enemy->cShape = cs;

		m_lastEnemyAddedFrame = gameFrame;
	}
}
