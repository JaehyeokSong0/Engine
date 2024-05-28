#include <PreCompiledHeader.h>
#include "Window.h"

namespace DemoEngine
{
	Window::Window(const wchar_t* name, unsigned int width, unsigned int height, WNDPROC MessageProcedure)
	{
		size_t length = wcslen(name) + 1;
		this->name = new wchar_t[length];
		memcpy(this->name, name, length);
		this->name[length - 1] = '0';

		instance = GetModuleHandle(nullptr);

		WNDCLASSEX wndClass = {};
		wndClass.cbSize = sizeof(wndClass);
		wndClass.hInstance = instance;
		wndClass.lpszClassName = TEXT("Engine Window Class");
		wndClass.style = CS_VREDRAW | CS_HREDRAW;
		wndClass.lpfnWndProc = MessageProcedure;

		if (!RegisterClassEx(&wndClass))
		{
			return;
		}

		RECT rect = { 0, 0, 1280, 800 };
		AdjustWindowRect(&rect, WS_OVERLAPPEDWINDOW, FALSE);

		int windowWidth = rect.right - rect.left;
		int windowHeight = rect.bottom - rect.top;

		int xPosition = (GetSystemMetrics(SM_CXSCREEN) - windowWidth) / 2;
		int yPosition = (GetSystemMetrics(SM_CYSCREEN) - windowHeight) / 2;

		handle = CreateWindow(
			wndClass.lpszClassName,
			name,
			WS_OVERLAPPEDWINDOW,
			xPosition, yPosition,
			windowWidth, windowHeight,
			nullptr, nullptr, wndClass.hInstance, nullptr
		);

		if (handle == nullptr)
		{
			return;
		}

		ShowWindow(handle, SW_SHOW);
		UpdateWindow(handle);
	}

	Window::~Window()
	{
		SafeDelete(name);
	}
	
	void Window::Run()
	{
		MSG message = {};
		while (message.message != WM_QUIT)
		{
			if (PeekMessage(&message, nullptr, 0u, 0u, PM_REMOVE))
			{
				TranslateMessage(&message);
				DispatchMessage(&message);
			}
			else
			{

			}
		}
	}
}