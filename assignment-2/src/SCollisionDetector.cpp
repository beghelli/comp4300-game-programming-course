#include <iostream>
#include "SCollisionDetector.h"

SCollisionDetector::SCollisionDetector() {}

void SCollisionDetector::process(EntityManager& entities)
{
	for (std::shared_ptr<Entity>& e : entities.getEntities())
	{
		if (e->cTransform && e->cCollision && e->cCollision->checkAgainstTags.size() > 0)
		{
			for (std::string tag : e->cCollision->checkAgainstTags)
			{
				auto entitiesToCheck = entities.getEntities(tag);
				for (std::shared_ptr<Entity>& ce : entitiesToCheck)
				{
					float collisionDistance = e->cCollision->collisionRadius + ce->cCollision->collisionRadius;
					if (std::abs(e->cTransform->pos.x - ce->cTransform->pos.x) <= collisionDistance
							&& std::abs(e->cTransform->pos.y - ce->cTransform->pos.y) <= collisionDistance)
					{
						e->cCollision->collided = true;
						ce->cCollision->collided = true;
					}
				}
			}
		}
	}
}
