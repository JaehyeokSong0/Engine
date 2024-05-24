#pragma once
#include "../DataType.h"

class VertexShader
{
public:
	~VertexShader();
	HRESULT Initialize(ID3D11Device* device);

	ID3DBlob* GetVertexBufferBlob() const;
	ID3D11VertexShader* GetVertexShader() const;
	ID3D11InputLayout* GetInputLayout() const;

private:
	ID3DBlob* vertexBufferBlob = nullptr;
	ID3D11VertexShader* vertexShader = nullptr;
	ID3D11InputLayout* inputLayout = nullptr;
};