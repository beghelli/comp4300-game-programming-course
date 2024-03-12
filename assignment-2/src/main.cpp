#include "Config.h"
#include "Game.h"

int main (int argc, char * argv[])
{
	Config config("config.txt");
	Game game(config);
	game.run();

	return 0;
}
