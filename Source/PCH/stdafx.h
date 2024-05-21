#pragma once

#ifdef _DEBUG
	#ifdef UNICODE
		#pragma comment(linker, "/entry:wWinMainCRTStartup /subsystem:console")
	#else
		#pragma comment(linker, "/entry:WinMainCRTStartup /subsystem:console")
	#endif
#endif

#include <Windows.h>
#include <wrl.h>

#include <d3d11.h>
#include <d3dcompiler.h>
#include <dxgi.h>

#include <iostream>
#include <source_location>

using namespace std;
using Microsoft::WRL::ComPtr;

void DebugLog(string str, const source_location& loc = source_location::current());