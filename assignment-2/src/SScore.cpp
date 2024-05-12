#include "SScore.h"

SScore::SScore() {}

SScore::SScore(sf::Font font)
	: m_font(font)
{}

void SScore::process(EntityManager& entities)
{
	for (std::shared_ptr<Entity>& player : entities.getEntities("Player"))
	{
		for (std::shared_ptr<Entity>& enemy : entities.getEntities("Enemy"))
		{
			if (enemy->cCollision && enemy->cCollision->collided && enemy->cCollision->collidedWithTag == "Bullet")
			{
				unsigned int value;
				value = enemy->cShape->shape.getPointCount() * 100;

				if (enemy->cLifeSpan)
				{
					value = value * 2;
				}

				player->cScore->score += value;
			}
		}

		if (player->cScore)
		{
			sf::Text text("Score: " + std::to_string(player->cScore->score), m_font, 30);
			text.setStyle(sf::Text::Bold);
			text.setFillColor(sf::Color::Red);
			text.setPosition(10,10);

			player->cScore->scoreText = text;
		}
	}
}
