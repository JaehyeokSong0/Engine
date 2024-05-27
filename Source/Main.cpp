#include <stdafx.h>
#include "Engine/Engine.h"

/* MEMO
 1. Struct
  - Game�� Engine�� ���
  - Engine�� Window* ����
  - Engine�� Renderer* ����
  - Shader�� Renderer�� ����
 2. Reminder
  - RTV ���� �� backBuffer release
  - FAILED(HRESULT)
 3. Debug
  - Debug mode������ console ���
  - Logger�� stdafx.h/DebugLog ���
*/ 

int APIENTRY wWinMain(
	_In_ HINSTANCE hInstance,
	_In_opt_ HINSTANCE hPrevInstance,
	_In_ LPWSTR lpCmdLine,
	_In_ int nShowCmd)
{
	HRESULT hr = S_OK;

	// ���� thread���� COM library �ʱ�ȭ
	hr = CoInitialize(NULL);
	if (FAILED(hr))
	{
		DebugLog("CoInitialize Failed");
		return hr;
	}

	Engine* engine = new Engine();
	hr = engine->Initialize(hInstance, TEXT("class"), TEXT("window"), 600, 800);
	if (FAILED(hr))
	{
		DebugLog("Engine initialization Failed");
		return hr;
	}
	engine->Run();

	delete engine;

	return 0;
}