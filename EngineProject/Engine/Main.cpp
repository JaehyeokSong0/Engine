#include <PreCompiledHeader.h>
#include "Device/Window.h"
#include "Game/Game.h"

using namespace DemoEngine;

Engine* g_Engine;

int main()
{
	Game* game = new Game(1280, 800);
	game->Run();

	delete game;
	return 0;
}