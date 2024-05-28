#pragma once

#include "../Engine/Engine.h"

namespace DemoEngine
{
	class Game : public Engine
	{
	public:
		Game(unsigned int width, unsigned int height);
		~Game();
	};
}