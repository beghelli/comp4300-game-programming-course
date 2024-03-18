#include <fstream>
#include <iostream>
#include <SFML/Graphics.hpp>
#include "Config.h"

Config::Config(const std::string& configFile)
	: m_configFile(configFile)
{
	read();
}

void Config::read()
{
	std::ifstream ifs(m_configFile);
	std::string type;
	int r, g, b;

	while (ifs >> type)
	{
		if (type == "Window")
		{
			ifs >> m_windowCfg.width;
			ifs >> m_windowCfg.height;
			ifs >> m_windowCfg.frameRate;
			(bool) ifs >> m_windowCfg.fullscreen;
		}

		if (type == "Font")
		{
			ifs >> m_fontCfg.font;
			ifs >> m_fontCfg.size;
			ifs >> r;
			ifs >> g;
			ifs >> b;
			m_fontCfg.color = sf::Color(r, g, b);
		}

		if (type == "Player")
		{
			ifs >> m_playerCfg.radius;
			ifs >> m_playerCfg.collisionRadius;
			ifs >> m_playerCfg.velocity;
			ifs >> r;
			ifs >> g;
			ifs >> b;
			m_playerCfg.fillColor = sf::Color(r, g, b);
			ifs >> r;
			ifs >> g;
			ifs >> b;
			m_playerCfg.outlineColor = sf::Color(r, g, b);
			ifs >> m_playerCfg.outlineThickness;
			ifs >> m_playerCfg.shapeVertices;
			ifs >> m_playerCfg.fireRate;
		}

		if (type == "Enemy")
		{
			ifs >> m_enemyCfg.radius;
			ifs >> m_enemyCfg.collisionRadius;
			ifs >> m_enemyCfg.velocity.min;
			ifs >> m_enemyCfg.velocity.max;
			ifs >> r;
			ifs >> g;
			ifs >> b;
			m_enemyCfg.outlineColor = sf::Color(r, g, b);
			ifs >> m_enemyCfg.outlineThickness;
			ifs >> m_enemyCfg.vertices.min;
			ifs >> m_enemyCfg.vertices.max;
			ifs >> m_enemyCfg.smallLifespan;
			ifs >> m_enemyCfg.spawnInterval;
		}

		if (type == "Bullet")
		{
			ifs >> m_bulletCfg.radius;
			ifs >> m_bulletCfg.collisionRadius;
			ifs >> m_bulletCfg.velocity;
			ifs >> r;
			ifs >> g;
			ifs >> b;
			m_bulletCfg.fillColor = sf::Color(r, g, b);
			ifs >> r;
			ifs >> g;
			ifs >> b;
			m_bulletCfg.outlineColor = sf::Color(r, g, b);
			ifs >> m_bulletCfg.outlineThickness;
			ifs >> m_bulletCfg.shapeVertices;
			ifs >> m_bulletCfg.lifespan;
		}
	}
}

Config::WindowCfg Config::getWindow() const
{
	return m_windowCfg;
}

Config::FontCfg Config::getFont() const
{
	return m_fontCfg;
}

Config::PlayerCfg Config::getPlayer() const
{
	return m_playerCfg;
}

Config::EnemyCfg Config::getEnemy() const
{
	return m_enemyCfg;
}

Config::BulletCfg Config::getBullet() const
{
	return m_bulletCfg;
}
