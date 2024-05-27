#pragma once
#include <WICTextureLoader.h>

class Texture final
{
public:
	Texture(LPCWSTR textureFilePath);
	~Texture();

	HRESULT Initialize(ID3D11Device* device, ID3D11DeviceContext* context);

	ID3D11SamplerState*& GetSamplerState();
	ID3D11ShaderResourceView*& GetTextureRV();
	
private:
	LPCWSTR filePath;

	ID3D11SamplerState* samplerState = nullptr;
	ID3D11ShaderResourceView* textureRV = nullptr;
};