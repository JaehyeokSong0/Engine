#include <stdafx.h>
#include "Engine/Engine.h"

/* MEMO
 1. Struct
  - Game�� Engine�� ���
  - Engine�� Window* ����
  - Engine�� Renderer* ����
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
	Engine* engine = new Engine();
	engine->Initialize(hInstance, TEXT("class"), TEXT("window"), 960, 540);
	engine->Run();

	delete engine;

	return 0;
}