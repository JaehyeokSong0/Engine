#pragma once
#include "../Shader/VertexShader.h"
#include "../Shader/PixelShader.h"
#include "../Texture/Texture.h"

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
	
	ID3D11Buffer* vertexBuffer = nullptr;
	ID3D11Buffer* indexBuffer = nullptr;

	ID3D11RasterizerState* rasterizerState = nullptr;

	VertexShader* vertexShader = nullptr;
	PixelShader* pixelShader = nullptr;
	Texture* texture = nullptr;
};