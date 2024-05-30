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
				handleKeysForEntity(event, e);
			}
			if (e->cMouseInput)
			{
				handleMouseForEntity(event, e);
			}
		}
	}
}

void SInput::handleKeysForEntity(sf::Event event, std::shared_ptr<Entity>& e)
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

void SInput::handleMouseForEntity(sf::Event event, std::shared_ptr<Entity>& e)
{
	if (event.type == sf::Event::MouseMoved)
	{
		e->cMouseInput->pos.x = event.mouseMove.x;
		e->cMouseInput->pos.y = event.mouseMove.y;
		e->cMouseInput->moved = true;
	}
	else
	{
		e->cMouseInput->moved = false;
	}

	if (event.type == sf::Event::MouseButtonPressed)
	{
		if (event.mouseButton.button == sf::Mouse::Left)
		{
			e->cMouseInput->leftClicked = true;
			e->cMouseInput->leftClickPos.x = event.mouseButton.x;
			e->cMouseInput->leftClickPos.y = event.mouseButton.y;
		}
		else
		{
			e->cMouseInput->leftClicked = false;
			e->cMouseInput->leftClickPos.x = 0;
			e->cMouseInput->leftClickPos.y = 0;
		}
		if (event.mouseButton.button == sf::Mouse::Right)
		{
			e->cMouseInput->rightClicked = true;
			e->cMouseInput->rightClickPos.x = event.mouseButton.x;
			e->cMouseInput->rightClickPos.y = event.mouseButton.y;
		}
		else
		{
			e->cMouseInput->rightClicked = false;
			e->cMouseInput->rightClickPos.x = 0;
			e->cMouseInput->rightClickPos.y = 0;
		}
	}
	else if (event.type == sf::Event::MouseButtonReleased)
	{
		if (event.mouseButton.button == sf::Mouse::Left)
		{
			e->cMouseInput->leftClicked = false;
			e->cMouseInput->leftClickPos.x = 0;
			e->cMouseInput->leftClickPos.y = 0;
		}
		if (event.mouseButton.button == sf::Mouse::Right)
		{
			e->cMouseInput->rightClicked = false;
			e->cMouseInput->rightClickPos.x = 0;
			e->cMouseInput->rightClickPos.y = 0;
		}
	}
}
