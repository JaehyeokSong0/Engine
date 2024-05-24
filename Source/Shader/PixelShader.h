#pragma once

class PixelShader
{
public:
	~PixelShader();
	HRESULT Initialize(ID3D11Device* device);

	ID3DBlob* GetPixelBuffer() const;
	ID3D11PixelShader* GetPixelShader() const;

private:
	ID3DBlob* pixelBuffer = nullptr;
	ID3D11PixelShader* pixelShader = nullptr;

	D3D11_BUFFER_DESC pbd = {};
	D3D11_SUBRESOURCE_DATA psd = {};
};