#include "SEnemySpawner.h"
#include "Entity.h"
#include "CTransform.h"
#include "CShape.h"

SEnemySpawner::SEnemySpawner() {}

SEnemySpawner::SEnemySpawner(
		Config::EnemyCfg enemyCfg,
		unsigned int windowWidth,
		unsigned int windowHeight)
	: m_enemyCfg(enemyCfg)
{
	m_enemySpawnWindowLimits.left = m_enemyCfg.radius;
	m_enemySpawnWindowLimits.right = windowWidth - m_enemyCfg.radius;
	m_enemySpawnWindowLimits.top = m_enemyCfg.radius;
	m_enemySpawnWindowLimits.bottom = windowHeight - m_enemyCfg.radius;;
}

void SEnemySpawner::process(
		EntityManager& entities,
		unsigned int gameFrame)
{
	unsigned int diffSinceLastAddition = gameFrame - m_lastEnemyAddedFrame;
	if (diffSinceLastAddition == 0 || diffSinceLastAddition == m_enemyCfg.spawnInterval)
	{
		std::shared_ptr<Entity> enemy = entities.addEntity("Enemy");
		std::shared_ptr<CTransform> ct = std::make_shared<CTransform>();

		unsigned int xPos = 1 + m_enemySpawnWindowLimits.left +
			(rand() % (m_enemySpawnWindowLimits.right - m_enemySpawnWindowLimits.left));
		unsigned int yPos = 1 + m_enemySpawnWindowLimits.top +
			(rand() % (m_enemySpawnWindowLimits.bottom - m_enemySpawnWindowLimits.top));

		unsigned int degrees = rand() % 361;
		unsigned int enemyVelocity = m_enemyCfg.velocity.min;
		if (m_enemyCfg.velocity.max > m_enemyCfg.velocity.min)
		{
			enemyVelocity = 1 + m_enemyCfg.velocity.min +
				(rand() % (m_enemyCfg.velocity.max - m_enemyCfg.velocity.min));
		}

		ct->pos = Vec2(xPos, yPos);
		ct->velocity = Vec2(enemyVelocity, 0);
		ct->velocity.rotate(degrees);
		enemy->cTransform = ct;

		sf::CircleShape shape(m_enemyCfg.radius, m_enemyCfg.vertices.max);
		shape.setOrigin(m_enemyCfg.radius, m_enemyCfg.radius);
		shape.setFillColor(sf::Color::Transparent);
		shape.setOutlineColor(m_enemyCfg.outlineColor);
		shape.setOutlineThickness(m_enemyCfg.outlineThickness);
		std::shared_ptr<CShape> cs = std::make_shared<CShape>(shape);
		enemy->cShape = cs;

		m_lastEnemyAddedFrame = gameFrame;
	}
}
