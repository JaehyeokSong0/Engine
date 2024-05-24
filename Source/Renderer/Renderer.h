#pragma once
#include "../Shader/VertexShader.h"
#include "../Shader/PixelShader.h"

class Renderer final
{
public:
	Renderer();
	~Renderer();
	HRESULT Initialize(HWND hWnd, int width, int height);

	HRESULT InitializeScene();
	HRESULT Render();

	HRESULT InitializeShaders();

	ID3D11Buffer* GetVertexBuffer() const;

private:
	ID3D11Device* device = nullptr;
	ID3D11DeviceContext* context = nullptr;
	IDXGISwapChain* swapChain = nullptr;
	ID3D11RenderTargetView* renderTargetView = nullptr;
	ID3D11DepthStencilView* depthStencilView = nullptr;
	ID3D11Texture2D* depthStencilBuffer = nullptr;
	ID3D11DepthStencilState* depthStencilState = nullptr;

	DXGI_SWAP_CHAIN_DESC swapChainDesc = {};
	D3D11_DEPTH_STENCIL_DESC depthStencilDesc = {};
	D3D11_TEXTURE2D_DESC depthStencilBufferDesc = {};

	VertexShader* vertexShader = nullptr;
	PixelShader* pixelShader = nullptr;
	
	ID3D11Buffer* vertexBuffer = nullptr;
	ComPtr<ID3D11Buffer> vertexBuffer2 = nullptr;
	D3D11_BUFFER_DESC vertexBufferDesc = {};
	D3D11_SUBRESOURCE_DATA vertexInitData = {};

	ID3D11RasterizerState* rasterizerState = nullptr;
};