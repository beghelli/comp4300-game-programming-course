#include <SFML/Graphics.hpp>
#include "SInput.h"

SInput::SInput() {}

void SInput::process(EntityManager& entities, sf::RenderWindow& window)
{
	sf::Event event;
	while (window.pollEvent(event))
	{
		if (event.type == sf::Event::Closed)
		{
			window.close();
		}
		for (std::shared_ptr<Entity>& e : entities.getEntities())
		{
			if (e->cInput)
			{
				handleForEntity(event, e);
			}
		}
	}
}

void SInput::handleForEntity(sf::Event event, std::shared_ptr<Entity>& e)
{
	if (event.type == sf::Event::KeyPressed)
	{
		if (event.key.code == sf::Keyboard::Key::D)
		{
			e->cInput->right = true;
		}
		else if (event.key.code == sf::Keyboard::Key::A)
		{
			e->cInput->left = true;
		}
		else if (event.key.code == sf::Keyboard::Key::W)
		{
			e->cInput->up = true;
		}
		else if (event.key.code == sf::Keyboard::Key::S)
		{
			e->cInput->down = true;
		}
	}
	else if (event.type == sf::Event::KeyReleased)
	{
		if (event.key.code == sf::Keyboard::Key::D)
		{
			e->cInput->right = false;
		}
		else if (event.key.code == sf::Keyboard::Key::A)
		{
			e->cInput->left = false;
		}
		else if (event.key.code == sf::Keyboard::Key::W)
		{
			e->cInput->up = false;
		}
		else if (event.key.code == sf::Keyboard::Key::S)
		{
			e->cInput->down = false;
		}
	}
}
