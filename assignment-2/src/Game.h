#include <iostream>

class Game
{
	const std::string& m_configFile;

public:
	Game(const std::string& configFile);
	int run();
};
