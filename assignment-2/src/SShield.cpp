#include <cmath>
#include <SFML/Graphics/CircleShape.hpp>
#include "SShield.h"
#include "CCollision.h"
#include "CTransform.h"
#include "CShape.h"

SShield::SShield() {};

void SShield::process(EntityManager& entities)
{
	for (std::shared_ptr<Entity>& e : entities.getEntities())
	{
		if (e->cShield && e->cMouseInput)
		{
			handleShield(e, entities);
		}

		if (e->cCollision && e->cCollision->collided && e->cCollision->collidedWithTag == "Shield")
		{
			std::shared_ptr<Entity>& shield = entities.getEntities("Shield").front();
			float x1 = e->cTransform->pos.x;
			float y1 = e->cTransform->pos.y;

			float x2 = shield->cTransform->pos.x;
			float y2 = shield->cTransform->pos.y;

			float newAngle = (180.0 / M_PI) * atan2(y2 - y1, x2 - x1);
			e->cTransform->velocity.rotate(newAngle);
			e->cCollision->collided = false;
			e->cCollision->collidedWithTag = "";
		}
	}
}

void SShield::handleShield(std::shared_ptr<Entity>& e, EntityManager& entities)
{
	EntityManager::VEntities& shieldEntities = entities.getEntities("Shield");

	if (e->cMouseInput->rightClicked)
	{
		if (shieldEntities.size() == 0)
		{
			createShield(e, entities);
		}
		else
		{
			std::shared_ptr<Entity>& shield = entities.getEntities("Shield").front();
			shield->cTransform->pos = e->cTransform->pos;
			shield->cTransform->velocity = e->cTransform->velocity;
		}
	}
	else
	{
		if (shieldEntities.size() != 0)
		{
			std::shared_ptr<Entity>& shield = entities.getEntities("Shield").front();
			shield->setActive(false);
		}
	}
}

void SShield::createShield(std::shared_ptr<Entity>& e, EntityManager& entities)
{
	std::cout << "Creating Shield" << std::endl;
	std::shared_ptr<Entity> shield = entities.addEntity("Shield");
	std::shared_ptr<CTransform> ct = std::make_shared<CTransform>();
	ct->pos = e->cTransform->pos;
	ct->velocity = e->cTransform->velocity;
	ct->maxVelocity = e->cTransform->maxVelocity;
	shield->cTransform = ct;

	float shieldRadius = e->cShape->shape.getRadius();
	shieldRadius += shieldRadius;

	sf::CircleShape shape(shieldRadius, 30);
	shape.setOrigin(shieldRadius, shieldRadius);
	sf::Color color = e->cShape->shape.getOutlineColor();
	color.a = 50;
	shape.setFillColor(color);
	std::shared_ptr<CShape> cs = std::make_shared<CShape>(shape);
	shield->cShape = cs;

	std::shared_ptr<CCollision> cc = std::make_shared<CCollision>();
	cc->collisionRadius = shieldRadius;
	cc->checkAgainstTags.push_back("Enemy");
	shield->cCollision = cc;
}
