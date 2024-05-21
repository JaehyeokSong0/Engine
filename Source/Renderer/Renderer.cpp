#include <stdafx.h>
#include "Renderer.h"

D3D_FEATURE_LEVEL featureLevels[] =
{
	D3D_FEATURE_LEVEL_11_0,
	D3D_FEATURE_LEVEL_11_1
};

// (TODO) ComPtr로 변환하기
Renderer::~Renderer()
{
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
}

HRESULT Renderer::Initialize(HWND hWnd, int width, int height)
{
	HRESULT hr = S_OK;

	// Initialize SwapChain description
	ZeroMemory(&scd, sizeof(DXGI_SWAP_CHAIN_DESC));

	scd.BufferDesc.Width = width;
	scd.BufferDesc.Height = height;
	scd.BufferDesc.RefreshRate.Denominator = 1;
	scd.BufferDesc.RefreshRate.Numerator = 60;
	scd.BufferDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
	scd.BufferDesc.ScanlineOrdering = DXGI_MODE_SCANLINE_ORDER_UNSPECIFIED;
	scd.BufferDesc.Scaling = DXGI_MODE_SCALING_UNSPECIFIED;
	scd.SampleDesc.Count = 1; // Sampling count
	scd.SampleDesc.Quality = 0; // 0 : No antialiasing
	scd.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;
	scd.BufferCount = 1;
	scd.OutputWindow = hWnd;
	scd.Windowed = true;
	scd.SwapEffect = DXGI_SWAP_EFFECT_DISCARD;
	scd.Flags = DXGI_SWAP_CHAIN_FLAG_ALLOW_MODE_SWITCH; // Full screen and windowed, resize available

	// Create Device & SwapChain
	hr = D3D11CreateDeviceAndSwapChain(
		nullptr, // NULL 넘기면 IDXGIFactory1::EnumAdapters의 첫 번째 인자 사용(default)
		D3D_DRIVER_TYPE_HARDWARE,
		NULL, // software rasterizer에 대한 handle. DriverType이 software인 경우 NOT NULL
		D3D11_CREATE_DEVICE_DEBUG, // device 생성에 사용되는 매개 변수
		featureLevels,
		_countof(featureLevels),
		D3D11_SDK_VERSION,
		&scd,
		&swapChain,
		&device,
		nullptr, // [out] device에서 지원하는 feature level
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
		backBuffer->Release(); // backBuffer는 COM 객체이므로 Release 메소드 존재
		backBuffer = nullptr;
	}
	if (FAILED(hr))
	{
		DebugLog("CreateRenderTargetView Failed");
		return hr;
	}
	
	// (TODO) DSV 위한 texture, dsv, stencilState 구현 후 OMSetRenderTargets()의 param[2] 변경
	// Create DSV
	/*hr = device->CreateDepthStencilView(
		backBuffer, nullptr, &depthStencilView);
	if (FAILED(hr))
	{
		DebugLog("CreateDepthStencilView Failed");
		return hr;
	}*/

	// Set RTV
	context->OMSetRenderTargets(
		1u, &renderTargetView, nullptr
	);

	return hr;
}
