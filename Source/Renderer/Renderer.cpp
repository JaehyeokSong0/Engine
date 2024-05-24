#include <stdafx.h>
#include "Renderer.h"

D3D_FEATURE_LEVEL featureLevels[] =
{
	D3D_FEATURE_LEVEL_11_0,
	D3D_FEATURE_LEVEL_11_1
};

Renderer::Renderer()
{
	vertexShader = new VertexShader();
	pixelShader = new PixelShader();
}

// (TODO) ComPtr�� ��ȯ�ϱ�
Renderer::~Renderer()
{
	// Release DX devices
	if (device != nullptr)
	{
		device->Release();
		device = nullptr;
	}
	if (context != nullptr)
	{
		context->Release();
		context = nullptr;
	}
	if (swapChain != nullptr)
	{
		swapChain->Release();
		swapChain = nullptr;
	}
	if (renderTargetView != nullptr)
	{
		renderTargetView->Release();
		renderTargetView = nullptr;
	}
	if (depthStencilView != nullptr)
	{
		depthStencilView->Release();
		depthStencilView = nullptr;
	}
	if (depthStencilBuffer != nullptr)
	{
		depthStencilBuffer->Release();
		depthStencilBuffer = nullptr;
	}
	if (depthStencilState != nullptr)
	{
		depthStencilState->Release();
		depthStencilState = nullptr;
	}
	
	// Delete Shaders
	if (vertexShader != nullptr)
	{
		delete vertexShader;
		vertexShader = nullptr;
	}
	if (pixelShader != nullptr)
	{
		delete pixelShader;
		pixelShader = nullptr;
	}

	// Delete vertex buffer
	if (vertexBuffer != nullptr)
	{
		vertexBuffer->Release();
		vertexBuffer = nullptr;
	}

	// Delete Rasterizer
	if (rasterizerState != nullptr)
	{
		rasterizerState->Release();
		rasterizerState = nullptr;
	}
}

// Initialize SwapChain, Device, RTV, DSV, Viewport
HRESULT Renderer::Initialize(HWND hWnd, int width, int height)
{
	HRESULT hr = S_OK;

	// Initialize SwapChain description
	ZeroMemory(&swapChainDesc, sizeof(DXGI_SWAP_CHAIN_DESC));
	swapChainDesc.BufferDesc.Width = width;
	swapChainDesc.BufferDesc.Height = height;
	swapChainDesc.BufferDesc.RefreshRate.Denominator = 1u;
	swapChainDesc.BufferDesc.RefreshRate.Numerator = 60u;
	swapChainDesc.BufferDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
	swapChainDesc.BufferDesc.ScanlineOrdering = DXGI_MODE_SCANLINE_ORDER_UNSPECIFIED;
	swapChainDesc.BufferDesc.Scaling = DXGI_MODE_SCALING_UNSPECIFIED;
	swapChainDesc.SampleDesc.Count = 1u; // Sampling count
	swapChainDesc.SampleDesc.Quality = 0u; // 0 : No antialiasing
	swapChainDesc.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;
	swapChainDesc.BufferCount = 1u;
	swapChainDesc.OutputWindow = hWnd;
	swapChainDesc.Windowed = TRUE;
	swapChainDesc.SwapEffect = DXGI_SWAP_EFFECT_DISCARD;
	swapChainDesc.Flags = DXGI_SWAP_CHAIN_FLAG_ALLOW_MODE_SWITCH; // Full screen and windowed, resize available

	// Create Device & SwapChain
	hr = D3D11CreateDeviceAndSwapChain(
		nullptr, // NULL �ѱ�� IDXGIFactory1::EnumAdapters�� ù ��° ���� ���(default)
		D3D_DRIVER_TYPE_HARDWARE,
		NULL, // software rasterizer�� ���� handle. DriverType�� software�� ��� NOT NULL
		D3D11_CREATE_DEVICE_DEBUG, // device ������ ���Ǵ� �Ű� ����
		featureLevels,
		_countof(featureLevels),
		D3D11_SDK_VERSION,
		&swapChainDesc,
		&swapChain,
		&device,
		nullptr, // [out] device���� �����ϴ� feature level
		&context);

	if (FAILED(hr))
	{
		DebugLog("D3D11CreateDeviceAndSwapChain Failed");
		return hr;
	}

	// Create backBuffer
	ID3D11Texture2D* backBuffer = nullptr;
	hr = swapChain->GetBuffer(0u, IID_PPV_ARGS(&backBuffer));
	if (FAILED(hr))
	{
		DebugLog("SwapChain GetBuffer Failed");
		return hr;
	}

	// Create RTV
	hr = device->CreateRenderTargetView(
		backBuffer, nullptr, &renderTargetView);
	if (backBuffer != nullptr)
	{
		backBuffer->Release(); // backBuffer�� COM ��ü�̹Ƿ� Release �޼ҵ� ����
		backBuffer = nullptr;
	}
	if (FAILED(hr))
	{
		DebugLog("CreateRenderTargetView Failed");
		return hr;
	}
	
	// Create depth stencil buffer 
	ZeroMemory(&depthStencilBufferDesc, sizeof(D3D11_TEXTURE2D_DESC));
	depthStencilBufferDesc.Width = width;
	depthStencilBufferDesc.Height = height;
	depthStencilBufferDesc.MipLevels = 1u;
	depthStencilBufferDesc.ArraySize = 1u;
	depthStencilBufferDesc.Format = DXGI_FORMAT_D24_UNORM_S8_UINT;
	depthStencilBufferDesc.SampleDesc.Count = 1u;
	depthStencilBufferDesc.SampleDesc.Quality = 0u;
	depthStencilBufferDesc.Usage = D3D11_USAGE_DEFAULT;
	depthStencilBufferDesc.BindFlags = D3D11_BIND_DEPTH_STENCIL;
	depthStencilBufferDesc.CPUAccessFlags = 0u;
	depthStencilBufferDesc.MiscFlags = 0u;

	hr = device->CreateTexture2D(
		&depthStencilBufferDesc, nullptr, &depthStencilBuffer);
	if (FAILED(hr))
	{
		DebugLog("CreateTexture2D Failed");
		return hr;
	}

	hr = device->CreateDepthStencilView(
		depthStencilBuffer, nullptr, &depthStencilView);
	if (FAILED(hr))
	{
		DebugLog("CreateDepthStencilView Failed");
		return hr;
	}

	// Set RTV
	context->OMSetRenderTargets(
		1u, &renderTargetView, depthStencilView
	);

	// Create depth stencil state
	depthStencilDesc.DepthEnable = TRUE;
	depthStencilDesc.DepthWriteMask = D3D11_DEPTH_WRITE_MASK_ALL; // Turn on writes to the depth-stencil buffer
	depthStencilDesc.DepthFunc = D3D11_COMPARISON_LESS_EQUAL;
	// D3D11_COMPARISON_LESS : If the source data is less than the destination data, the comparison passes
	// => �׸��� ������ �� �տ� ���� ���� ���� ����
	// D3D11_COMPARISON_EQUAL : If the source data is equal to the destination data, the comparison passes
	
	hr = device->CreateDepthStencilState(&depthStencilDesc, &depthStencilState);
	if (FAILED(hr))
	{
		DebugLog("CreateDepthStencilState Failed");
		return hr;
	}

	// Create & Set Viewport
	D3D11_VIEWPORT viewport = {};
	viewport.TopLeftX = 0.0f;
	viewport.TopLeftY = 0.0f;
	viewport.Width = static_cast<float>(width);
	viewport.Height = static_cast<float>(height);
	viewport.MinDepth = 0.0f;
	viewport.MaxDepth = 1.0f;

	context->RSSetViewports(
		1u, &viewport
	);
	
	// Create Rasterizer
	D3D11_RASTERIZER_DESC rasterizerDesc = {};
	//ZeroMemory(&rasterizerDesc, sizeof(D3D11_RASTERIZER_DESC));
	rasterizerDesc.FillMode = D3D11_FILL_SOLID;
	rasterizerDesc.CullMode = D3D11_CULL_BACK; // Do not draw backward primitives
	rasterizerDesc.FrontCounterClockwise = FALSE;
	hr = device->CreateRasterizerState(
		&rasterizerDesc,
		&rasterizerState
	);
	if (FAILED(hr))
	{
		DebugLog("CreateRasterizerState Failed");
		return hr;
	}

	// Set Shaders
	hr = InitializeShaders();
	if (FAILED(hr))
	{
		DebugLog("InitializeShaders Failed");
		return hr;
	}

	hr = InitializeScene();
	if (FAILED(hr))
	{
		DebugLog("InitializeScene Failed");
		return hr;
	}

	return hr;
}

HRESULT Renderer::InitializeShaders()
{
	HRESULT hr = S_OK;

	hr = vertexShader->Initialize(device);
	if (FAILED(hr))
	{
		DebugLog("VertexShader Initialization Failed");
		return hr;
	}

	hr = pixelShader->Initialize(device);
	if (FAILED(hr))
	{
		DebugLog("PixelShader Initialization Failed");
		return hr;
	}
	
	return hr;
}

HRESULT Renderer::InitializeScene()
{
	HRESULT hr = S_OK;

	// TEST CODE
	Vertex testVertex[] =
	{
		Vertex(XMFLOAT3(-0.5f, -0.5f, 0.5f), XMFLOAT4(1.0f, 0.0f, 0.0f, 1.0f)),
		Vertex(XMFLOAT3(0.0f, 0.5f, 0.5f), XMFLOAT4(0.0f, 1.0f, 0.0f, 1.0f)),
		Vertex(XMFLOAT3(0.5f, -0.5f, 0.5f), XMFLOAT4(0.0f, 0.0f, 1.0f, 1.0f))
	};
	Vertex testVertex2[] =
	{
		Vertex(XMFLOAT3(-0.5f, 0.25f, 0.0f), XMFLOAT4(0.0f, 1.0f, 1.0f, 1.0f)),
		Vertex(XMFLOAT3(0.5f, 0.25f, 0.0f), XMFLOAT4(1.0f, 0.0f, 1.0f, 1.0f)),
		Vertex(XMFLOAT3(-0.5f, -0.25f, 1.0f), XMFLOAT4(1.0f, 1.0f, 0.0f, 1.0f))
	};

	// Same as 'vertexBufferDesc = {};'
	ZeroMemory(&vertexBufferDesc, sizeof(D3D11_BUFFER_DESC));
	vertexBufferDesc.ByteWidth = sizeof(Vertex) * _countof(testVertex);
	vertexBufferDesc.Usage = D3D11_USAGE_DEFAULT;
	vertexBufferDesc.BindFlags = D3D11_BIND_VERTEX_BUFFER;
	vertexBufferDesc.CPUAccessFlags = 0u; // 0 : NO CPU Access

	ZeroMemory(&vertexInitData, sizeof(D3D11_SUBRESOURCE_DATA));
	vertexInitData.pSysMem = testVertex; // pSysMem : �ʱ�ȭ ������

	hr = device->CreateBuffer(&vertexBufferDesc, &vertexInitData, &vertexBuffer);
	if (FAILED(hr))
	{
		DebugLog("CreateBuffer Failed");
		return hr;
	}

	// TEST CODE
	ZeroMemory(&vertexBufferDesc, sizeof(D3D11_BUFFER_DESC));
	vertexBufferDesc.ByteWidth = sizeof(Vertex) * _countof(testVertex2);
	ZeroMemory(&vertexInitData, sizeof(D3D11_SUBRESOURCE_DATA));
	vertexInitData.pSysMem = testVertex2; 
	hr = device->CreateBuffer(&vertexBufferDesc, &vertexInitData, vertexBuffer2.GetAddressOf());
	if (FAILED(hr))
	{
		DebugLog("CreateBuffer Failed 2");
		return hr;
	}

	return hr;
}

HRESULT Renderer::Render()
{
	HRESULT hr = S_OK;

	// TEST CODE
	float testBgColor[] = { 0.0f, 0.0f, 0.0f, 1.0f };
	
	context->ClearRenderTargetView(renderTargetView, testBgColor);
	UINT clearFlags = D3D11_CLEAR_DEPTH | D3D11_CLEAR_STENCIL;
	context->ClearDepthStencilView(
		depthStencilView, 
		clearFlags, 
		1.0f, // Value to clear depth
		0u // Value to clear stencil
	);  

	context->IASetInputLayout(vertexShader->GetInputLayout());
	context->VSSetShader(vertexShader->GetVertexShader(), NULL, 0u);
	context->PSSetShader(pixelShader->GetPixelShader(), NULL, 0u);

	context->RSSetState(rasterizerState);
	context->OMSetDepthStencilState(depthStencilState, 0u);

	UINT offset = 0;
	UINT stride = sizeof(Vertex);
	context->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);
	
	context->IASetVertexBuffers(0u, 1u, &vertexBuffer, &stride, &offset);
	context->Draw(3u, 0u);

	context->IASetVertexBuffers(0u, 1u, vertexBuffer2.GetAddressOf(), &stride, &offset);
	context->Draw(3u, 0u);

	hr = swapChain->Present(0u, 0u); // DXGI_SWAP_EFFECT_DISCARD�� �� : SyncInterval = 0 -> ��� present + ����ȭ ����
	if (FAILED(hr))
	{
		DebugLog("Present Failed");
		return hr;
	}

	return hr;
}



ID3D11Buffer* Renderer::GetVertexBuffer() const
{
	return this->vertexBuffer;
}