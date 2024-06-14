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

HRESULT Texture::Initialize(ID3D11Device* device, ID3D11DeviceContext* context, aiColor3D* color)
{
	HRESULT hr = S_OK;
	
	this->color = *color;
	/*hr = CreateWICTextureFromFile(device, filePath, nullptr, &textureRV);
	if (FAILED(hr))
	{
		DebugLog("CreateWICTextureFromFile Failed");
		return hr;
	}*/

	// Create texture description
	CD3D11_TEXTURE2D_DESC textureDesc = {}; // TODO 
	textureDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
	textureDesc.Width = 1;
	textureDesc.Height = 1;
	textureDesc.SampleDesc.Count = 1;
	textureDesc.SampleDesc.Quality = 0;
	textureDesc.Usage = D3D11_USAGE_DEFAULT;
	textureDesc.BindFlags = D3D11_BIND_SHADER_RESOURCE | D3D11_BIND_RENDER_TARGET;
	textureDesc.CPUAccessFlags = 0;

	D3D11_SUBRESOURCE_DATA initData = {};
	initData.pSysMem = color;
	initData.SysMemPitch = sizeof(color);

	ID3D11Texture2D* texture = nullptr;
	hr = device->CreateTexture2D(&textureDesc, &initData, &texture);
	if (FAILED(hr))
	{
		DebugLog("CreateTexture2D Failed");
		return hr;
	}	
	textureResource = static_cast<ID3D11Texture2D*>(texture);

	CD3D11_SHADER_RESOURCE_VIEW_DESC shaderRVDesc = {};
	shaderRVDesc.ViewDimension = D3D11_SRV_DIMENSION_TEXTURE2D;
	shaderRVDesc.Format = textureDesc.Format;

	hr = device->CreateShaderResourceView(textureResource, &shaderRVDesc, &textureRV);
	if (FAILED(hr))
	{
		DebugLog("CreateShaderResourceView Failed");
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

HRESULT Texture::Initialize(ID3D11Device* device, ID3D11DeviceContext* context, LPCWSTR textureFilePath)
{
	SetFilePath(textureFilePath);
	aiColor3D defaultAiColor(0.0f, 0.0f, 0.0f);
	return Initialize(device, context, &defaultAiColor);
}

ID3D11SamplerState*& Texture::GetSamplerState() 
{
	return this->samplerState;
}

ID3D11ShaderResourceView*& Texture::GetTextureRV()
{
	return this->textureRV;
}

void Texture::SetFilePath(LPCWSTR textureFilePath)
{
	filePath = textureFilePath;
}
