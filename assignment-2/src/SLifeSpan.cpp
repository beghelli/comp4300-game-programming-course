#include <cmath>
#include <SFML/Graphics/RenderWindow.hpp>
#include "SLifeSpan.h"

SLifeSpan::SLifeSpan() {}

void SLifeSpan::process(EntityManager& entities)
{
	for (std::shared_ptr<Entity>& e : entities.getEntities())
	{
		if (e->cLifeSpan)
		{
			if (e->cShape)
			{
				sf::Shape& shape = e->cShape->shape;

				sf::Color color = shape.getFillColor();

				double lifePercentage = e->cLifeSpan->ageInFrames / (e->cLifeSpan->lifeSpan + 1.0);
				unsigned int alpha = floor((1 - lifePercentage) * 255);
				color.a = alpha;

				shape.setFillColor(color);
				shape.setOutlineColor(color);
			}

			e->cLifeSpan->ageInFrames++;

			if (e->cLifeSpan->ageInFrames == e->cLifeSpan->lifeSpan)
			{
				e->setActive(false);
			}
		}
	}

}
