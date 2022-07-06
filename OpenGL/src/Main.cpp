#include "../resources/header/Game.h"

int main()
{
	Game* game = new Game;
	if (game->Init())
		game->Run();

	return 0;
}