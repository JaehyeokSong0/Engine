#include <stdafx.h>
#include "Engine/Engine.h"

/* MEMO
 1. Struct
  - Game은 Engine을 상속
  - Engine이 Window* 보유
  - Engine이 Renderer* 보유
 2. Reminder
  - RTV 생성 후 backBuffer release
  - FAILED(HRESULT)
 3. Debug
  - Debug mode에서만 console 출력
  - Logger는 stdafx.h/DebugLog 사용
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