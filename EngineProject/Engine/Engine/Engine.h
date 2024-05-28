#pragma once

#include <Windows.h>

namespace DemoEngine
{
	class Engine
	{
	public:
		Engine(const wchar_t* name, unsigned int width, unsigned int height);
		virtual ~Engine();

		void Run();
		void Update();

		struct ID3D11Device* Device();
		struct ID3D11DeviceContext* Context();
		struct IDXGISwapChain* SwapChain();

		static LRESULT CALLBACK MessageProcedure(HWND handle, UINT message, WPARAM wparam, LPARAM lparam);

	protected:
		virtual void ProcessInput();
		virtual void Update(float deltaTime);
		virtual void Draw();

	private:
		void BeginScene(float* backgroundColor);
		void DrawScene();
		void EndScene();

	protected:
		struct ID3D11Device* device = nullptr;
		struct ID3D11DeviceContext* context = nullptr;
		struct IDXGISwapChain* swapChain = nullptr;
		struct ID3D11RenderTargetView* renderTargetView = nullptr;
		struct ID3D11DepthStencilView* depthStencilView = nullptr;

		class Window* window = nullptr;
		class Mesh* mesh = nullptr;
		class EngineShader* shader = nullptr;
	};
}

extern DemoEngine::Engine* g_Engine;