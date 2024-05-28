#include <PreCompiledHeader.h>
#include "EngineShader.h"
#include "../Engine/Engine.h"

namespace DemoEngine
{
	EngineShader::EngineShader(const wchar_t* filename)
	{
		wchar_t buffer[256];
		swprintf(buffer, 256, TEXT("D3DShader/%s"), filename);
		ThrowIfFailed(
			D3DCompileFromFile(buffer, nullptr, nullptr, "vsmain", "vs_5_0", 0u, 0u, &vertexShaderBuffer, nullptr),
			TEXT("Failed to compile vertex shader"));

		auto device = g_Engine->Device();
		ThrowIfFailed(
			device->CreateVertexShader(vertexShaderBuffer->GetBufferPointer(), vertexShaderBuffer->GetBufferSize(), nullptr, &vertexShader),
			TEXT("Failed to create vertex shader."));

		ThrowIfFailed(
			D3DCompileFromFile(buffer, nullptr, nullptr, "psmain", "ps_5_0", 0u, 0u, &pixelShaderBuffer, nullptr),
			TEXT("Failed to compile pixel shader"));

		ThrowIfFailed(
			device->CreatePixelShader(pixelShaderBuffer->GetBufferPointer(), pixelShaderBuffer->GetBufferSize(), nullptr, &pixelShader),
			TEXT("Failed to create pixel shader."));

		//LPCSTR SemanticName;
		//UINT SemanticIndex;
		//DXGI_FORMAT Format;
		//UINT InputSlot;
		//UINT AlignedByteOffset;
		//D3D11_INPUT_CLASSIFICATION InputSlotClass;
		//UINT InstanceDataStepRate;
		D3D11_INPUT_ELEMENT_DESC inputElementDesc[] =
		{
			{ "POSITION", 0u, DXGI_FORMAT_R32G32B32_FLOAT, 0u, D3D11_APPEND_ALIGNED_ELEMENT, D3D11_INPUT_PER_VERTEX_DATA, 0u }
		};

		ThrowIfFailed(
			device->CreateInputLayout(
				inputElementDesc,
				_countof(inputElementDesc),
				vertexShaderBuffer->GetBufferPointer(),
				vertexShaderBuffer->GetBufferSize(),
				&inputlayout), 
			TEXT("Failed to create input layout"));
	}
	
	EngineShader::~EngineShader()
	{
		SafeRelease(inputlayout);
		SafeRelease(vertexShaderBuffer);
		SafeRelease(vertexShader);
		SafeRelease(pixelShaderBuffer);
		SafeRelease(pixelShader);
	}
	
	void EngineShader::Bind()
	{
		auto context = g_Engine->Context();
		context->IASetInputLayout(inputlayout);
		context->VSSetShader(vertexShader, nullptr, 0u);
		context->PSSetShader(pixelShader, nullptr, 0u);
	}

	ID3DBlob* EngineShader::VertexShaderBuffer() const
	{
		return vertexShaderBuffer;
	}
}
