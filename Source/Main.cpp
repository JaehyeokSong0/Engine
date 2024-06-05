#include <stdafx.h>
#include "Engine/Engine.h"

int APIENTRY wWinMain(
	_In_ HINSTANCE hInstance,
	_In_opt_ HINSTANCE hPrevInstance,
	_In_ LPWSTR lpCmdLine,
	_In_ int nShowCmd)
{
	HRESULT hr = S_OK;

	// Initialize COM library on current thread
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

#ifdef _DEBUG
	CheckMemoryLeak();
#endif
	return 0;
}