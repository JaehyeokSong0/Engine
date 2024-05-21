#pragma once

class Renderer final
{
public:
	~Renderer();
	HRESULT Initialize(HWND hWnd, int width, int height);

private:
	ID3D11Device* device = nullptr;
	ID3D11DeviceContext* context = nullptr;
	IDXGISwapChain* swapChain = nullptr;
	ID3D11RenderTargetView* renderTargetView = nullptr;
	ID3D11DepthStencilView* depthStencilView = nullptr;

	DXGI_SWAP_CHAIN_DESC scd = {};
	D3D11_DEPTH_STENCIL_VIEW_DESC dsvd = {};
};