#pragma once

#include <PreCompiledHeader.h>

namespace DemoEngine
{	
	class EngineShader
	{
	public:
		EngineShader(const wchar_t* filename);
		virtual ~EngineShader();

		virtual void Bind();

		ID3DBlob* VertexShaderBuffer() const;

	protected:
		ID3D11InputLayout* inputlayout = nullptr;
		
		ID3DBlob* vertexShaderBuffer = nullptr;
		ID3D11VertexShader* vertexShader = nullptr;

		ID3DBlob* pixelShaderBuffer = nullptr;
		ID3D11PixelShader* pixelShader = nullptr;
	};
}