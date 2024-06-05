#pragma once
#include "../Shader/Shader.h"
#include "../Texture/Texture.h"
#include "../Buffer/Buffer.h"
#include "../Camera/Camera.h"
#include "../Model/Model.h"

class Renderer final
{
public:
	Renderer();
	~Renderer();

	HRESULT Initialize(HWND hWnd, int width, int height);

	HRESULT InitializeScene();
	HRESULT Render();

	HRESULT InitializeShaders();

	Camera* GetCamera();

	// TEST CODE
	void DestroyTest();

private:
	int width;
	int height;

	ID3D11Device* device = nullptr;
	ID3D11DeviceContext* context = nullptr;
	IDXGISwapChain* swapChain = nullptr;
	ID3D11RenderTargetView* renderTargetView = nullptr;
	ID3D11DepthStencilView* depthStencilView = nullptr;
	ID3D11Texture2D* depthStencilBuffer = nullptr;
	ID3D11DepthStencilState* depthStencilState = nullptr;
	
	VertexBuffer* vertexBuffer = nullptr;
	IndexBuffer* indexBuffer = nullptr;
	ConstantBuffer* constantBuffer = nullptr; // (TODO) Rename later
	ID3D11RasterizerState* rasterizerState = nullptr;

	VertexShader* vertexShader = nullptr;
	PixelShader* pixelShader = nullptr;
	Texture* texture = nullptr;

	Camera* camera = nullptr;

	Model* testModel = nullptr;
};