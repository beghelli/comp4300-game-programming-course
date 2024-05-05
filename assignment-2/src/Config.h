#pragma once
#include <iostream>
#include <SFML/Graphics.hpp>

class Config
{
public:
	template <typename T>
	struct Interval
	{
		T min;
		T max;
	};

	struct WindowCfg
	{
		unsigned int width;
		unsigned int height;
		unsigned int frameRate;
		bool fullscreen;
 	};

	struct FontCfg
	{
		std::string font;
		unsigned int size;
		sf::Color color;
	};

	struct PlayerCfg
	{
		unsigned int radius;
		unsigned int collisionRadius;
		float velocity;
		sf::Color fillColor;
		sf::Color outlineColor;
		unsigned int outlineThickness;
		unsigned int shapeVertices;
		unsigned int fireRate;
	};

	struct EnemyCfg
	{
		unsigned int radius;
		unsigned int collisionRadius;
		Interval<int> velocity;
		sf::Color outlineColor;
		unsigned int outlineThickness;
		Interval<int> vertices;
		unsigned int smallLifespan;
		unsigned int spawnInterval;
	};

	struct BulletCfg
	{
		unsigned int radius;
		unsigned int collisionRadius;
		float velocity;
		sf::Color fillColor;
		sf::Color outlineColor;
		unsigned int outlineThickness;
		unsigned int shapeVertices;
		unsigned int lifespan;
	};

private:
	const std::string& m_configFile;
	WindowCfg m_windowCfg;
	FontCfg m_fontCfg;
	PlayerCfg m_playerCfg;
	EnemyCfg m_enemyCfg;
	BulletCfg m_bulletCfg;

	void read();
public:
	Config(const std::string& configFile);
	WindowCfg getWindow() const;
	FontCfg getFont() const;
	PlayerCfg getPlayer() const;
	EnemyCfg getEnemy() const;
	BulletCfg getBullet() const;
};
