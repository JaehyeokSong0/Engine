#include <PreCompiledHeader.h>
#include "Game.h"

namespace DemoEngine
{
	Game::Game(unsigned int width, unsigned int height)
		: Engine(TEXT("Game"), width, height)
	{
	}

	Game::~Game()
	{
	}
}