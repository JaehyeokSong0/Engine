#include <stdafx.h>

void DebugLog(string str, const source_location& loc)
{
#ifdef _DEBUG
	cout << "[" << loc.function_name() << "] (" << loc.line() << ":" << loc.column() << ")\n" << str << "\n";
#endif
}

void DebugLog(wstring wstr, const source_location& loc)
{
#ifdef _DEBUG
	wcout << "[" << loc.function_name() << "] (" << loc.line() << ":" << loc.column() << ")\n" << wstr << "\n";
#endif
}

#include <dxgidebug.h>
#include <D3D11SDKLayers.h>
#ifdef _DEBUG
void CheckMemoryLeak()
{
	HMODULE dxgidebugDll = GetModuleHandleW(L"dxgidebug.dll");
	decltype(&DXGIGetDebugInterface) GetDebugInterface = reinterpret_cast<decltype(&DXGIGetDebugInterface)>(GetProcAddress(dxgidebugDll, "DXGIGetDebugInterface"));

	IDXGIDebug* debug;

	GetDebugInterface(IID_PPV_ARGS(&debug));
	OutputDebugStringW(L"=== [START] d3d memory leak check ===\n");
	debug->ReportLiveObjects(DXGI_DEBUG_D3D11, DXGI_DEBUG_RLO_DETAIL);
	OutputDebugStringW(L"=== [END] d3d memory leak check ===\n");

	debug->Release();
}
#endif