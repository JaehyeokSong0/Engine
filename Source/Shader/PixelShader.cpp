#include <stdafx.h>
#include "PixelShader.h"

PixelShader::~PixelShader()
{
	if (pixelBufferBlob != nullptr)
	{
		pixelBufferBlob->Release();
		pixelBufferBlob = nullptr;
	}
	if (pixelShader != nullptr)
	{
		pixelShader->Release();
		pixelShader = nullptr;
	}
}

HRESULT PixelShader::Initialize(ID3D11Device* device)
{
	HRESULT hr = S_OK;

	// Set Pixel Shader buffer
	ID3DBlob* errorMsgs = nullptr;
	LPCWSTR shaderPath = L"Shader/PixelShader.hlsl";
	hr = D3DCompileFromFile(
		shaderPath,
		nullptr, // Define
		nullptr, // Include
		"PSMain", "ps_5_0",
		0u, 0u, // Flags
		&pixelBufferBlob,
		&errorMsgs);
	if (FAILED(hr))
	{
		DebugLog("D3DCompileFromFile Failed");
		DebugLog(static_cast<char*>(errorMsgs->GetBufferPointer()));
		errorMsgs->Release();
		return hr;
	}
	errorMsgs = nullptr;

	// Create Pixel Shader
	hr = device->CreatePixelShader(
		pixelBufferBlob->GetBufferPointer(),
		pixelBufferBlob->GetBufferSize(),
		nullptr,
		&pixelShader);
	if (FAILED(hr))
	{
		DebugLog("CreatePixelShader Failed");
		return hr;
	}

	return hr;
}

ID3DBlob* PixelShader::GetPixelBuffer() const
{
    return this->pixelBufferBlob;
}

ID3D11PixelShader* PixelShader::GetPixelShader() const
{
    return this->pixelShader;
}
