#include <fstream>
#include <iostream>
#include <SFML/Graphics.hpp>
#include <memory>

class GameConfig
{
	public:
	struct WindowConfig
	{
		int width;
		int height;
	};

	struct FontConfig
	{
		std::string path;
		int size;
		int redColor;
		int greenColor;
		int blueColor;
	};

	struct ShapeConfig
	{
		std::string name;
		float posX;
		float posY;
		float speedX;
		float speedY;
		int redColor;
		int greenColor;
		int blueColor;
	};

	struct RectangleConfig
	{
		ShapeConfig shapeConfig;
		float width;
		float height;
	};

	struct CircleConfig
	{
		ShapeConfig shapeConfig;
		float radius;
	};

	private:
	const std::string m_filePath;
	WindowConfig m_windowConfig;
	FontConfig m_fontConfig;
	std::vector<RectangleConfig> m_rectConfig;
	std::vector<CircleConfig> m_circleConfig;

	void readConfigFile()
	{
		std::ifstream fin(m_filePath);
		std::string type;

		while (fin >> type)
		{
			if (type == "Window")
			{
				fin >> m_windowConfig.width;
				fin >> m_windowConfig.height;
			}
			else if (type == "Font")
			{
				fin >> m_fontConfig.path;
				fin >> m_fontConfig.size;
				fin >> m_fontConfig.redColor;
				fin >> m_fontConfig.greenColor;
				fin >> m_fontConfig.blueColor;
			}
			else if (type == "Rectangle")
			{
				RectangleConfig rc;
				fin >> rc.shapeConfig.name;
				fin >> rc.shapeConfig.posX;
				fin >> rc.shapeConfig.posY;
				fin >> rc.shapeConfig.speedX;
				fin >> rc.shapeConfig.speedY;
				fin >> rc.shapeConfig.redColor;
				fin >> rc.shapeConfig.greenColor;
				fin >> rc.shapeConfig.blueColor;
				fin >> rc.width;
				fin >> rc.height;

				m_rectConfig.push_back(rc);
			}
			else if (type == "Circle")
			{
				CircleConfig cc;
				fin >> cc.shapeConfig.name;
				fin >> cc.shapeConfig.posX;
				fin >> cc.shapeConfig.posY;
				fin >> cc.shapeConfig.speedX;
				fin >> cc.shapeConfig.speedY;
				fin >> cc.shapeConfig.redColor;
				fin >> cc.shapeConfig.greenColor;
				fin >> cc.shapeConfig.blueColor;
				fin >> cc.radius;

				m_circleConfig.push_back(cc);
			}
		}
	}

	public:

	GameConfig(const std::string filePath)
		: m_filePath(filePath)
	{
		readConfigFile();
	}

	~GameConfig() {}

	const std::string getFilePath()
	{
		return m_filePath;
	}

	const WindowConfig getWindowConfig()
	{
		return m_windowConfig;
	}

	const FontConfig getFontConfig()
	{
		return m_fontConfig;
	}

	const std::vector<RectangleConfig> getRectConfigs()
	{
		return m_rectConfig;
	}

	const std::vector<CircleConfig> getCircleConfigs()
	{
		return m_circleConfig;
	}

};

class Entity
{
	float m_speedX;
	float m_speedY;
	std::shared_ptr<sf::Shape> m_shape;
	sf::Text m_title;

	public:

	Entity(std::shared_ptr<sf::Shape> shape)
		: m_shape(shape)
	{}

	~Entity()
	{
	}

	void setSpeedX(float speedX)
	{
		m_speedX = speedX;
	}

	float getSpeedX()
	{
		return m_speedX;
	}

	void setSpeedY(float speedY)
	{
		m_speedY = speedY;
	}

	float getSpeedY()
	{
		return m_speedY;
	}

	void setTitle(const sf::Text& title)
	{
		m_title = title;
	}

	sf::Text& getTitle()
	{
		return m_title;
	}

	std::shared_ptr<sf::Shape> getShape()
	{
		return m_shape;
	}

	void updatePosition(const GameConfig::WindowConfig& wConfig)
	{
		std::shared_ptr<sf::Shape> shape = getShape();
		sf::Vector2f cPos = shape->getPosition();
		float newPosX, newPosY;
		newPosX = cPos.x + m_speedX;
		newPosY = cPos.y + m_speedY;
		const sf::FloatRect localBounds = shape->getLocalBounds();

		if (newPosX <= 0 || newPosX + localBounds.width >= wConfig.width)
		{
			m_speedX *= -1.0f;
			newPosX = cPos.x + m_speedX;
		}
		if (newPosY <= 0 || newPosY + localBounds.height >= wConfig.height)
		{
			m_speedY *= -1.0f;
			newPosY = cPos.y + m_speedY;
		}

		const sf::FloatRect textLocalBounds = m_title.getLocalBounds();
		m_title.setPosition(newPosX + (localBounds.width / 2.0f),
				newPosY + (localBounds.height / 2.0f));

		shape->setPosition(newPosX, newPosY);
	}
};

void applyShapeConfig(std::shared_ptr<sf::Shape> shape, const GameConfig::ShapeConfig& config)
{
	shape->setFillColor(sf::Color(config.redColor, config.greenColor, config.blueColor));
	shape->setPosition(config.posX, config.posY);
}

Entity createEntity(
		std::shared_ptr<sf::Shape>     shape,
		const GameConfig::ShapeConfig& config,
		const sf::Font&                font,
		const GameConfig::FontConfig&  fConfig
	)
{
		Entity e(shape);
		e.setSpeedX(config.speedX);
		e.setSpeedY(config.speedY);

		sf::Text title;
		title.setFont(font);
		title.setString(config.name);
		title.setCharacterSize(fConfig.size);
		title.setFillColor(sf::Color(fConfig.redColor, fConfig.greenColor, fConfig.blueColor));
		sf::FloatRect lb = title.getLocalBounds();
		title.setOrigin(lb.left + lb.width / 2.0f, lb.top + lb.height / 2.0f);
		e.setTitle(title);

		return e;
}

void initializeEntities(GameConfig config, std::vector<Entity>& entities, const sf::Font& font)
{
	const GameConfig::FontConfig& fConfig = config.getFontConfig();
	for (GameConfig::RectangleConfig config : config.getRectConfigs())
	{
		std::shared_ptr<sf::Shape> rect = std::make_shared<sf::RectangleShape>(sf::Vector2f(config.width, config.height));
		applyShapeConfig(rect, config.shapeConfig);
		Entity e = createEntity(rect, config.shapeConfig, font, fConfig);
		entities.push_back(e);
	}

	for (GameConfig::CircleConfig config : config.getCircleConfigs())
	{
		std::shared_ptr<sf::Shape> c = std::make_shared<sf::CircleShape>(config.radius);
		applyShapeConfig(c, config.shapeConfig);
		Entity e = createEntity(c, config.shapeConfig, font, fConfig);
		entities.push_back(e);
	}
}

int main(int argc, char * argv[])
{
	GameConfig config("config.txt");
	std::vector<Entity> entities;

	sf::Font font;
	if (! font.loadFromFile(config.getFontConfig().path))
	{
		std::cerr << "Failed loading font." << std::endl;
	}
	initializeEntities(config, entities, font);

	const GameConfig::WindowConfig wConfig = config.getWindowConfig();
	sf::RenderWindow window(sf::VideoMode(wConfig.width, wConfig.height), "My Game");
	window.setFramerateLimit(420);

	while (window.isOpen())
	{
		sf::Event event;
		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
			{
				window.close();
			}
		}

		window.clear();
		for (Entity& e : entities)
		{
			std::shared_ptr<sf::Shape> shape = e.getShape();
			e.updatePosition(wConfig);
			window.draw(*shape);
			window.draw(e.getTitle());
		}
		window.display();
	}

	return 0;
}
