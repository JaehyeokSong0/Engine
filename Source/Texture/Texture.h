#pragma once
#include <WICTextureLoader.h>
class Texture final
{
public:
	Texture() = default;
	Texture(LPCWSTR textureFilePath);
	~Texture();

	HRESULT Initialize(ID3D11Device* device, ID3D11DeviceContext* context);
	HRESULT Initialize(ID3D11Device* device, ID3D11DeviceContext* context, LPCWSTR textureFilePath);

	ID3D11SamplerState*& GetSamplerState();
	ID3D11ShaderResourceView*& GetTextureRV();

	void SetFilePath(LPCWSTR textureFilePath);
	
private:
	LPCWSTR filePath;

	ID3D11SamplerState* samplerState = nullptr;
	ID3D11ShaderResourceView* textureRV = nullptr;
};