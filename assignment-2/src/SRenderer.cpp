#include "SRenderer.h"

SRenderer::SRenderer() {}

void SRenderer::process(EntityManager& entities, sf::RenderWindow& window)
{
	window.clear();
	for (std::shared_ptr<Entity>& e : entities.getEntities())
	{
		if (e->cShape)
		{
			sf::Shape& shape = e->cShape->shape;
			window.draw(shape);
		}

		if (e->cScore)
		{
			window.draw(e->cScore->scoreText);
		}
	}

	window.display();
}
