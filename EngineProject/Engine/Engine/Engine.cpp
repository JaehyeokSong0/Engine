#include <PreCompiledHeader.h>
#include "Engine.h"
#include "../Device/Window.h"
#include "../Render/Mesh.h"
#include "../EngineShader/EngineShader.h"

namespace DemoEngine
{
	Engine::Engine(const wchar_t* name, unsigned int width, unsigned int height)
	{
		// 글로벌 엔진 객체 설정.
		g_Engine = this;
		
		window = new Window(name, width, height, MessageProcedure);

		unsigned int deviceFlag = 0u;

#if _DEBUG
		deviceFlag |= D3D11_CREATE_DEVICE_DEBUG;
#endif

		D3D_FEATURE_LEVEL featureLevels[] =
		{
			D3D_FEATURE_LEVEL_11_1,
			D3D_FEATURE_LEVEL_11_0,
		};

		DXGI_SWAP_CHAIN_DESC swapChainDesc = {};
		swapChainDesc.BufferCount = 1;
		swapChainDesc.BufferDesc.Width = width;
		swapChainDesc.BufferDesc.Height = height;
		swapChainDesc.BufferDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
		swapChainDesc.Windowed = true;
		swapChainDesc.OutputWindow = window->handle;
		swapChainDesc.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;
		swapChainDesc.SampleDesc.Count = 1;
		swapChainDesc.SampleDesc.Quality = 0;
		swapChainDesc.SwapEffect = DXGI_SWAP_EFFECT_DISCARD;

		// 장치(그래픽카드) 초기화.
		ThrowIfFailed(D3D11CreateDeviceAndSwapChain(
			nullptr,
			D3D_DRIVER_TYPE_HARDWARE,
			nullptr,
			deviceFlag,
			featureLevels,
			_countof(featureLevels),
			D3D11_SDK_VERSION,
			&swapChainDesc,
			&swapChain,
			&device,
			nullptr,
			&context
		), TEXT("Failed to create device and swap chain"));

		// Render Target View 생성.
		ID3D11Texture2D* backbuffer = nullptr;
		//swapChain->GetBuffer(0u, __uuidof(ID3D11Texture2D), reinterpret_cast<void**>(&backbuffer));
		ThrowIfFailed(swapChain->GetBuffer(0u, IID_PPV_ARGS(&backbuffer)), TEXT("Failed to get back buffer"));
		
		ThrowIfFailed(device->CreateRenderTargetView(
			backbuffer,
			nullptr,
			&renderTargetView
		), TEXT("Failed to create render target view."));
		SafeRelease(backbuffer);

		// RTV 할당.
		context->OMSetRenderTargets(1u, &renderTargetView, nullptr);

		// 뷰포트 생성 및 할당.
		D3D11_VIEWPORT viewport = { };
		viewport.TopLeftX = 0.0f;
		viewport.TopLeftY = 0.0f;
		viewport.Width = static_cast<float>(width);
		viewport.Height = static_cast<float>(height);
		viewport.MinDepth = 0.0f;
		viewport.MaxDepth = 1.0f;

		context->RSSetViewports(1u, &viewport);

		// 메시 생성.
		float vertices[] =
		{
			-0.5f, -0.5f, 0.5f,
			 0.0f,  0.5f, 0.5f,
			 0.5f, -0.5f, 0.5f
		};

		unsigned int indices[] { 0, 1, 2};

		mesh = new Mesh(vertices, _countof(vertices), indices, _countof(indices));

		// 쉐이더 객체 생성.
		shader = new EngineShader(TEXT("Shader.hlsl"));
	}

	Engine::~Engine()
	{
		SafeDelete(window);
		SafeDelete(mesh);
		SafeDelete(shader);

		SafeRelease(device);
		SafeRelease(context);
		SafeRelease(swapChain);
		SafeRelease(renderTargetView);
		SafeRelease(depthStencilView);
	}

	void Engine::Run()
	{
		MSG message = {};
		while (message.message != WM_QUIT)
		{
			if (PeekMessage(&message, nullptr, 0u, 0u, PM_REMOVE))
			{
				TranslateMessage(&message);
				DispatchMessage(&message);
			}
			else
			{
				Update();
			}
		}
	}
	
	void Engine::Update()
	{
		ProcessInput();
		Update(0.0f);
		Draw();
	}

	ID3D11Device* Engine::Device()
	{
		return device;
	}

	ID3D11DeviceContext* Engine::Context()
	{
		return context;
	}

	IDXGISwapChain* Engine::SwapChain()
	{
		return swapChain;
	}
	
	LRESULT Engine::MessageProcedure(HWND handle, UINT message, WPARAM wparam, LPARAM lparam)
	{
		switch (message)
		{
		case WM_DESTROY:
			PostQuitMessage(0);
			return 0;

		case WM_KEYDOWN:
			if (wparam == VK_ESCAPE)
			{
				if (MessageBox(handle, TEXT("Want to quit?"), TEXT("Quit Engine"), MB_YESNO) == IDYES)
				{
					DestroyWindow(handle);
					return 0;
				}
			}
			return 0;
		}

		return DefWindowProc(handle, message, wparam, lparam);
	}
	
	void Engine::ProcessInput()
	{
	}
	
	void Engine::Update(float deltaTime)
	{
	}
	
	void Engine::Draw()
	{
		// Clear.
		float backgroundColor[] = { 0.6f, 0.8f, 0.9f ,1.0f };
		BeginScene(backgroundColor);

		// Draw.
		DrawScene();

		// Present.
		EndScene();
	}

	void Engine::BeginScene(float* backgroundColor)
	{
		context->ClearRenderTargetView(renderTargetView, backgroundColor);
	}
	
	void Engine::DrawScene()
	{
		mesh->Bind();
		shader->Bind();

		context->DrawIndexed(mesh->IndexCount(), 0u, 0u);
	}
	
	void Engine::EndScene()
	{
		swapChain->Present(0u, 0u);
	}
}