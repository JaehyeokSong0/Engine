#pragma once

#ifdef _DEBUG
	#ifdef UNICODE
		#pragma comment(linker, "/entry:wWinMainCRTStartup /subsystem:console")
	#else
		#pragma comment(linker, "/entry:WinMainCRTStartup /subsystem:console")
	#endif
#endif

#define ToString(Text) #Text
#define ToWideString(Text) L#Text

#include <Windows.h>
#include <wrl.h>

#include <d3d11.h>
#include <d3dcompiler.h>
#include <dxgi.h>

#include <iostream>
#include <source_location>
#include <string>

#include <vector>

// #include<DirectXMath.h>
// using namespace DirectX;
#include "../DataType.h" 

using namespace std;
using namespace Microsoft::WRL;

void DebugLog(string str, const source_location& loc = source_location::current());
void DebugLog(wstring wstr, const source_location& loc = source_location::current());