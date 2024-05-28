#pragma once

#include <Windows.h>

namespace DemoEngine
{
	class Window
	{
		friend class Engine;

	public:
		Window(const wchar_t* name, unsigned int width, unsigned int height, WNDPROC MessageProcedure);
		~Window();

		void Run();

	private:
		wchar_t* name = nullptr;
		HWND handle = nullptr;
		HINSTANCE instance = nullptr;
		unsigned int width = 0u;
		unsigned int height = 0u;
	};
}
