#include <stdafx.h>
#include "Texture.h"

Texture::Texture(LPCWSTR textureFilePath) 
	:filePath(textureFilePath)
{}

Texture::~Texture()
{
	if (samplerState != nullptr)
	{
		samplerState->Release();
		samplerState = nullptr;
	}	
	if (textureRV != nullptr)
	{
		textureRV->Release();
		textureRV = nullptr;
	}
}

HRESULT Texture::Initialize(ID3D11Device* device, ID3D11DeviceContext* context)
{
	HRESULT hr = S_OK;

	hr = CreateWICTextureFromFile(device, filePath, nullptr, &textureRV);
	if (FAILED(hr))
	{
		DebugLog("CreateWICTextureFromFile Failed");
		return hr;
	}

	// Create Sampler state description
	D3D11_SAMPLER_DESC samplerDesc = {};
	samplerDesc.Filter = D3D11_FILTER_MIN_MAG_MIP_LINEAR; // use linear interpolation
	samplerDesc.AddressU = D3D11_TEXTURE_ADDRESS_WRAP; // repeated texture (Tile)
	samplerDesc.AddressV = D3D11_TEXTURE_ADDRESS_WRAP;
	samplerDesc.AddressW = D3D11_TEXTURE_ADDRESS_WRAP;
	samplerDesc.ComparisonFunc = D3D11_COMPARISON_NEVER;
	samplerDesc.MinLOD = 0.0f;
	samplerDesc.MaxLOD = D3D11_FLOAT32_MAX;
	hr = device->CreateSamplerState(&samplerDesc, &samplerState);
	if (FAILED(hr))
	{
		DebugLog("CreateSamplerState Failed");
		return hr;
	}

	return hr;
}

ID3D11SamplerState*& Texture::GetSamplerState() 
{
	return this->samplerState;
}

ID3D11ShaderResourceView*& Texture::GetTextureRV()
{
	return this->textureRV;
}
