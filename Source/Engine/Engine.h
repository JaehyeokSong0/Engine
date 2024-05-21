#pragma once
#include "../Window/Window.h"

class Engine
{
public:
	Engine();
	virtual ~Engine();

	void Initialize(
		HINSTANCE hInstance, LPCTSTR className, LPCTSTR windowName,
		int width, int height);
	void Run();

	bool ProcessMessage();
	void Update();
	void Render();
protected:
private:
	Window* window = nullptr;
};