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
	ZeroMemory(&message, sizeof(message));

	while (PeekMessage(&message,
		NULL, // NULL�� ��� ���� �������� ��� â�� ���� message �˻�
		0u, // minimum message filter
		0u, // maximum message filter, �˻��� �޽��� ������ ����
		PM_REMOVE)) // PeekMessage ���� �ش� message ����
	{
		if (message.message == WM_QUIT)
		{
			DebugLog("ProcessMessage: WM_QUIT");
			return false;
		}
		
		if (message.message == WM_LBUTTONUP)
		{
			window->GetMouse()->AlterMouseMode();
		}

		if (message.message == WM_MOUSEMOVE)
		{
			MouseRelativeMove mouseMove = window->GetMouse()->GetMouseDragState();
			XMFLOAT3 relativePos = XMFLOAT3(static_cast<float>(mouseMove.x) / 10.0f, static_cast<float>(mouseMove.y) / 10.0f, 0.0f);
			
			renderer->GetCamera()->Move(relativePos);
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
	renderer->Render();
}