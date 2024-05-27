#include <stdafx.h>
#include "VertexShader.h"
#include "PixelShader.h"

D3D11_INPUT_ELEMENT_DESC inputElementDesc[] =
{
	{
		"POSITION", // Semantic name
		0u, // Semantic index
		DXGI_FORMAT_R32G32B32_FLOAT, // Format
		0u, // Input Slot
		D3D11_APPEND_ALIGNED_ELEMENT, // Aligned byte offset
		D3D11_INPUT_PER_VERTEX_DATA, // Input slot class
		0u  // Instance data step rate. per-vertex data 포함 시 반드시 0 할당 
	}
	,
	{
		"TEXCOORD",
		0u,
		DXGI_FORMAT_R32G32_FLOAT,
		0u,
		D3D11_APPEND_ALIGNED_ELEMENT,
		D3D11_INPUT_PER_VERTEX_DATA,
		0u
	}
};

VertexShader::~VertexShader()
{
	if (vertexBufferBlob != nullptr)
	{
		vertexBufferBlob->Release();
		vertexBufferBlob = nullptr;
	}
	if (vertexShader != nullptr)
	{
		vertexShader->Release();
		vertexShader = nullptr;
	}
	if (inputLayout != nullptr)
	{
		inputLayout->Release();
		inputLayout = nullptr;
	}
}

HRESULT VertexShader::Initialize(ID3D11Device* device)
{
	HRESULT hr = S_OK;

	// Set Vertex Shader buffer
	ID3DBlob* errorMsgs = nullptr;
	LPCWSTR shaderPath = L"Shader/VertexShader.hlsl";
	hr = D3DCompileFromFile(
		shaderPath,
		nullptr, // Define
		nullptr, // Include
		"VSMain", "vs_5_0",
		0u, 0u, // Flags
		&vertexBufferBlob,
		&errorMsgs);
	if (FAILED(hr))
	{
		DebugLog("D3DCompileFromFile Failed");
		DebugLog(static_cast<char*>(errorMsgs->GetBufferPointer()));
		errorMsgs->Release();
		return hr;
	}
	errorMsgs = nullptr;

	// Create Vertex Shader
	hr = device->CreateVertexShader(
		vertexBufferBlob->GetBufferPointer(),
		vertexBufferBlob->GetBufferSize(),
		nullptr,
		&vertexShader);
	if (FAILED(hr))
	{
		DebugLog("CreateVertexShader Failed");
		return hr;
	}

	// Create Input Layout
	hr = device->CreateInputLayout(
		inputElementDesc, _countof(inputElementDesc),
		vertexBufferBlob->GetBufferPointer(), vertexBufferBlob->GetBufferSize(),
		&inputLayout);
	if (FAILED(hr))
	{
		DebugLog("CreateInputLayout Failed");
		return hr;
	}

	return hr;
}

ID3DBlob* VertexShader::GetVertexBufferBlob() const
{
	return this->vertexBufferBlob;
}

ID3D11VertexShader* VertexShader::GetVertexShader() const
{
	return this->vertexShader;
}

ID3D11InputLayout* VertexShader::GetInputLayout() const
{
	return this->inputLayout;
}