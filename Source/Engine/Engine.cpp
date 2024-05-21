#include <stdafx.h>
#include "Engine.h"

Engine::Engine()
{
	window = new Window();
}

Engine::~Engine()
{
	if (window != nullptr)
	{
		delete window;
		window = nullptr;
	}
}

void Engine::Initialize(
	HINSTANCE hInstance, LPCTSTR className, LPCTSTR windowName,
	int width, int height)
{
	window->Initialize(hInstance, className, windowName, width, height);
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
		NULL, // NULL�� ��� ���� �������� ��� â�� ���� message �˻�
		0u, // minimum message filter
		0u, // maximum message filter, �˻��� �޽��� ������ ����
		PM_REMOVE)) // PeekMessage ���� �ش� message ����
	{
		if (message.message == WM_QUIT)
		{
			DebugLog("Engine: WM_QUIT");
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