#pragma once

class VertexShader
{
public:
	~VertexShader();
	HRESULT Initialize(ID3D11Device* device);
	
	ID3D11VertexShader* GetVertexShader();
	ID3D11InputLayout* GetInputLayout();
private:
	ID3D11InputLayout* inputLayout;

	ID3D11VertexShader* vertexShader;
	ID3DBlob* vertexBuffer;

	D3D11_BUFFER_DESC bd;
	D3D11_SUBRESOURCE_DATA sd;
};