#pragma once

#include <Windows.h>

#include <d3d11.h>
#include <dxgi.h>
#include <d3dcompiler.h>

#include <vector>
#include <string>

template<typename Type>
void SafeDelete(Type* pointer)
{
	if (pointer != nullptr)
	{
		delete pointer;
		pointer = nullptr;
	}
}

template<typename Type>
void SafeRelease(Type* pointer)
{
	if (pointer != nullptr)
	{
		pointer->Release();
		pointer = nullptr;
	}
}

__forceinline void ThrowIfFailed(HRESULT result, const wchar_t* errorMessage)
{
	if (FAILED(result))
	{
		MessageBox(nullptr, errorMessage, TEXT("DX Error"), MB_OK);
		__debugbreak();
		return;
	}
}