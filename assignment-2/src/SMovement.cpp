#include "SMovement.h"

SMovement::SMovement() {}

void SMovement::process(EntityManager& entities)
{
	for (std::shared_ptr<Entity>& e : entities.getEntities())
	{
		if (e->cTransform && e->cShape)
		{
			sf::Shape& shape = e->cShape->shape;
			if (e->cInput)
			{
				float velocity = e->cTransform->maxVelocity;
				if (e->cInput->right)
				{
					e->cTransform->velocity.x = velocity;
				}
				else if (e->cInput->left)
				{
					e->cTransform->velocity.x = -1 * velocity;
				}
				else
				{
					e->cTransform->velocity.x = 0;
				}

				if (e->cInput->up)
				{
					e->cTransform->velocity.y = -1 * velocity;
				}
				else if (e->cInput->down)
				{
					e->cTransform->velocity.y = velocity;
				}
				else
				{
					e->cTransform->velocity.y = 0;
				}
			}

			Vec2 newPos = e->cTransform->pos + e->cTransform->velocity;
			shape.setPosition(newPos.x, newPos.y);
		}
	}
}
