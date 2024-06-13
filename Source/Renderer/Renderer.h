#pragma once
#include "../Shader/Shader.h"
#include "../Buffer/Buffer.h"
#include "../Camera/Camera.h"
#include "../Model/Model.h"
#include "../Object/Object.h"

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
	
	ID3D11RasterizerState* rasterizerState = nullptr;

	VertexShader* vertexShader = nullptr;
	PixelShader* pixelShader = nullptr;

	Camera* camera = nullptr;

	// TEST
	Object* testObject = nullptr;
	Model* testModel = nullptr;
};