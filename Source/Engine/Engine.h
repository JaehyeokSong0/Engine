#pragma once
#include "../Window/Window.h"
#include "../Renderer/Renderer.h"

class Engine
{
public:
	Engine();
	virtual ~Engine();

	HRESULT Initialize(
		HINSTANCE hInstance, LPCTSTR className, LPCTSTR windowName,
		int width, int height);
	void Run();

	bool ProcessMessage();
	void Update();
	void Render();

private:
	Window* window = nullptr;
	Renderer* renderer = nullptr;
};