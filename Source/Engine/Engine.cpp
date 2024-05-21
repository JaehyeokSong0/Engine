#include <stdafx.h>
#include "Engine.h"

Engine::Engine()
{
	window = new Window();
	renderer = new Renderer();
}

Engine::~Engine()
{
	if (window != nullptr)
	{
		delete window;
		window = nullptr;
	}
	if (renderer != nullptr)
	{
		delete renderer;
		renderer = nullptr;
	}
}

HRESULT Engine::Initialize(
	HINSTANCE hInstance, LPCTSTR className, LPCTSTR windowName,
	int width, int height)
{
	HRESULT hr = S_OK;
	
	hr = window->Initialize(hInstance, className, windowName, width, height);
	if (FAILED(hr))
	{
		DebugLog("Window Initialization Failed");
		return hr;
	}

	hr = renderer->Initialize(window->GetHandle(), width, height);
	if (FAILED(hr))
	{
		DebugLog("Renderer Initialization Failed");
		return hr;
	}

	return hr;
}

void Engine::Run()
{
	while (ProcessMessage())
	{
		Update();
		Render();
	}
}

bool Engine::ProcessMessage()
{
	MSG message;
	ZeroMemory(&message, sizeof(MSG));

	while (PeekMessage(&message,
		NULL, // NULL인 경우 현재 스레드의 모든 창에 대한 message 검색
		0u, // minimum message filter
		0u, // maximum message filter, 검사할 메시지 범위를 지정
		PM_REMOVE)) // PeekMessage 이후 해당 message 삭제
	{
		if (message.message == WM_QUIT)
		{
			DebugLog("ProcessMessage: WM_QUIT");
			return false;
		}
		
		TranslateMessage(&message);
		DispatchMessage(&message);
	}
	return true;
}

void Engine::Update()
{
}

void Engine::Render()
{

}