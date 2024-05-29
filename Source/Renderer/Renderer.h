#pragma once
#include "../Shader/Shader.h"
#include "../Texture/Texture.h"
#include "../Buffer/Buffer.h"
#include "../Camera/Camera.h"

class Renderer final
{
public:
	Renderer();
	~Renderer();

	HRESULT Initialize(HWND hWnd, int width, int height);

	HRESULT InitializeScene();
	HRESULT Render();

	HRESULT InitializeShaders();

	VertexBuffer* GetVertexBuffer() const;

private:
	ID3D11Device* device = nullptr;
	ID3D11DeviceContext* context = nullptr;
	IDXGISwapChain* swapChain = nullptr;
	ID3D11RenderTargetView* renderTargetView = nullptr;
	ID3D11DepthStencilView* depthStencilView = nullptr;
	ID3D11Texture2D* depthStencilBuffer = nullptr;
	ID3D11DepthStencilState* depthStencilState = nullptr;
	
	VertexBuffer* vertexBuffer = nullptr;
	IndexBuffer* indexBuffer = nullptr;
	ConstantBuffer* objectCB = nullptr;
	ConstantBuffer* cameraCB = nullptr;
	ID3D11RasterizerState* rasterizerState = nullptr;

	VertexShader* vertexShader = nullptr;
	PixelShader* pixelShader = nullptr;
	Texture* texture = nullptr;

	Camera* camera = nullptr;
};