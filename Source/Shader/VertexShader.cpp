#include <stdafx.h>
#include "VertexShader.h"

D3D11_INPUT_ELEMENT_DESC inputElementDesc[] =
{
	{"POSITION", // Semantic name
	0u, // Semantic index
	DXGI_FORMAT_R32G32B32_FLOAT, // Format
	0u, // Input Slot
	D3D11_APPEND_ALIGNED_ELEMENT, // Aligned byte offset
	D3D11_INPUT_PER_VERTEX_DATA, // Input slot class
	0u } // Instance data step rate. per-vertex data 포함 시 반드시 0 할당
};

VertexShader::~VertexShader()
{
	if (inputLayout != nullptr)
	{
		inputLayout->Release();
		inputLayout = nullptr;
	}
	if (vertexShader != nullptr)
	{
		vertexShader->Release();
		vertexShader = nullptr;
	}
	if (vertexBuffer != nullptr)
	{
		vertexBuffer->Release();
		vertexBuffer = nullptr;
	}
}

HRESULT VertexShader::Initialize(ID3D11Device* device)
{
	HRESULT hr = S_OK;

	hr = device->CreateInputLayout(
		inputElementDesc, _countof(inputElementDesc),
		vertexBuffer->GetBufferPointer(), vertexBuffer->GetBufferSize(),
		&inputLayout);
	
	if (FAILED(hr))
	{
		DebugLog("CreateInputLayout Failed");
		return hr;
	}

	return hr;
}

ID3D11VertexShader* VertexShader::GetVertexShader()
{
	return nullptr;
}

ID3D11InputLayout* VertexShader::GetInputLayout()
{
	return nullptr;
}
