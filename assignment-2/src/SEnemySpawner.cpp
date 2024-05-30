#include "CCollision.h"
#include "CTransform.h"
#include "CShape.h"
#include "Entity.h"
#include "SEnemySpawner.h"
#include "Vec2.h"

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
		std::shared_ptr<CCollision> cc = std::make_shared<CCollision>();
		cc->collisionRadius = m_enemyCfg.radius;
		enemy->cCollision = cc;

		unsigned int xPos = m_enemySpawnWindowLimits.left +
			(rand() % (m_enemySpawnWindowLimits.right - m_enemySpawnWindowLimits.left));
		unsigned int yPos = m_enemySpawnWindowLimits.top +
			(rand() % (m_enemySpawnWindowLimits.bottom - m_enemySpawnWindowLimits.top));

		unsigned int degrees = rand() % 360;
		unsigned int enemyVelocity = m_enemyCfg.velocity.min;
		if (m_enemyCfg.velocity.max > m_enemyCfg.velocity.min)
		{
			enemyVelocity = m_enemyCfg.velocity.min +
				(rand() % (m_enemyCfg.velocity.max - m_enemyCfg.velocity.min));
		}

		ct->pos = Vec2(xPos, yPos);
		ct->velocity = Vec2(enemyVelocity, 0);
		ct->velocity.rotate(degrees);
		ct->rotationVelocity = enemyVelocity;
		enemy->cTransform = ct;

		unsigned int vertices = m_enemyCfg.vertices.min +
			(rand() % (m_enemyCfg.vertices.max - m_enemyCfg.vertices.min));
		sf::CircleShape shape(m_enemyCfg.radius, vertices);
		shape.setOrigin(m_enemyCfg.radius, m_enemyCfg.radius);

		unsigned int red = 1 + rand() % 254;
		unsigned int green = 1 + rand() % 254;
		unsigned int blue = 1 + rand() % 254;
		sf::Color color(red, green, blue, 255);

		shape.setFillColor(color);
		shape.setOutlineColor(m_enemyCfg.outlineColor);
		shape.setOutlineThickness(m_enemyCfg.outlineThickness);
		std::shared_ptr<CShape> cs = std::make_shared<CShape>(shape);
		enemy->cShape = cs;

		std::vector<std::string> tags {"Player", "Bullet"};
		std::shared_ptr<CEntityLife> cel = std::make_shared<CEntityLife>(tags);
		enemy->cEntityLife = cel;

		m_lastEnemyAddedFrame = gameFrame;
	}

	float degreesIncrease;
	float s_degrees;
	Vec2 pos;
	std::size_t s_vertices;
	for (std::shared_ptr<Entity>& e : entities.getEntitiesDeleted())
	{
		if (e->tag() == "Enemy" && ! e->cLifeSpan)
		{
			pos = e->cTransform->pos;
			s_vertices = e->cShape->shape.getPointCount();
			degreesIncrease = 360 / s_vertices;
			s_degrees = 0;

			for (int i = 0; i < s_vertices; i++)
			{
				std::shared_ptr<Entity> smallEnemy = entities.addEntity("Enemy");
				std::shared_ptr<CTransform> s_ct = std::make_shared<CTransform>();
				std::shared_ptr<CCollision> s_cc = std::make_shared<CCollision>();
				s_cc->collisionRadius = m_enemyCfg.radius / 2;
				smallEnemy->cCollision = s_cc;

				s_ct->pos = pos;
				s_ct->velocity = e->cTransform->velocity;
				s_ct->velocity.rotate(s_degrees);
				s_ct->rotationVelocity = e->cTransform->rotationVelocity;
				smallEnemy->cTransform = s_ct;

				sf::CircleShape s_shape(s_cc->collisionRadius, s_vertices);
				s_shape.setOrigin(s_cc->collisionRadius, s_cc->collisionRadius);
				s_shape.setFillColor(e->cShape->shape.getFillColor());
				s_shape.setOutlineColor(e->cShape->shape.getOutlineColor());
				s_shape.setOutlineThickness(e->cShape->shape.getOutlineThickness());
				std::shared_ptr<CShape> s_cs = std::make_shared<CShape>(s_shape);
				smallEnemy->cShape = s_cs;

				std::shared_ptr<CLifeSpan> s_cls = std::make_shared<CLifeSpan>(m_enemyCfg.smallLifespan);
				smallEnemy->cLifeSpan = s_cls;

				std::vector<std::string> tags {"Player", "Bullet"};
				std::shared_ptr<CEntityLife> cel = std::make_shared<CEntityLife>(tags);
				smallEnemy->cEntityLife = cel;

				s_degrees += degreesIncrease;
			}
		}
	}
}
