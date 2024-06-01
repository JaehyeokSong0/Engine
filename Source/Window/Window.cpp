#include <stdafx.h>
#include "Window.h"

Window::~Window()
{
    if (mouse != nullptr)
    {
        delete mouse;
        mouse = nullptr;
    }
    if (keyboard != nullptr)
    {
        delete keyboard;
        keyboard = nullptr;
    }
}

HWND Window::GetHandle() const
{
    return this->hWnd;
}

HINSTANCE Window::GetInstance() const
{
    return this->hInstance;
}

LPCTSTR Window::GetClassName() const
{
    return this->className;
}

LRESULT Window::WindowProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
    switch (uMsg)
    {
        case WM_CREATE:
            DebugLog("WindowProc: WM_CREATE");
            return 0;
        case WM_DESTROY:
            DebugLog("WindowProc: WM_DESTROY");
            PostQuitMessage(0);
            return 0;
        case WM_ACTIVATEAPP:
            Mouse::ProcessMessage(uMsg, wParam, lParam);
            Keyboard::ProcessMessage(uMsg, wParam, lParam);
            return 0;
#pragma region MouseEvent
        case WM_ACTIVATE:
        case WM_INPUT:
        case WM_MOUSEMOVE:
        case WM_LBUTTONDOWN:
        case WM_LBUTTONUP:
        case WM_RBUTTONDOWN:
        case WM_RBUTTONUP:
        case WM_MBUTTONDOWN:
        case WM_MBUTTONUP:
        case WM_MOUSEWHEEL:
        case WM_XBUTTONDOWN:
        case WM_XBUTTONUP:
        case WM_MOUSEHOVER:
#pragma endregion MouseEvent
        {
            Mouse::ProcessMessage(uMsg, wParam, lParam);
            return 0;
        }
#pragma region KeyboardEvent
        case WM_KEYDOWN:
        case WM_KEYUP:
        case WM_SYSKEYUP:
#pragma endregion KeyboardEvent
        {
            Keyboard::ProcessMessage(uMsg, wParam, lParam);
            return 0;
        }
        default:
            return DefWindowProc(hWnd, uMsg, wParam, lParam);
    }
}

HRESULT Window::Initialize(
    HINSTANCE hInstance, LPCTSTR className, LPCTSTR windowName,
    int width = CW_USEDEFAULT, int height = CW_USEDEFAULT)
{
    HRESULT hr = S_OK;

    this->hInstance = hInstance;
    this->className = className;
    this->windowName = windowName;
    this->width = width;
    this->height = height;

    hr = RegisterWindow();
    if(FAILED(hr))
    {
        DebugLog("RegisterWindow Failed");
        return hr;
    }
    
    // Resize window
    DWORD dwStyle = WS_CAPTION | WS_MINIMIZEBOX | WS_SYSMENU;
    int centerScreenX = (GetSystemMetrics(SM_CXSCREEN) - width) / 2;
    int centerScreenY = (GetSystemMetrics(SM_CYSCREEN) - height) / 2;

    RECT windowRect = {};
    windowRect.left = centerScreenX;
    windowRect.right = windowRect.left + width;
    windowRect.top = centerScreenY;
    windowRect.bottom = windowRect.top + height;
    AdjustWindowRect(&windowRect, dwStyle, FALSE);

    this->hWnd = CreateWindowEx(
        WS_OVERLAPPED,
        className,
        windowName,
        dwStyle, 
        windowRect.left, 
        windowRect.top,
        windowRect.right - windowRect.left,
        windowRect.bottom - windowRect.top,
        nullptr,
        nullptr,
        this->hInstance,
        nullptr
    );

    if (this->hWnd == nullptr)
    {
        DebugLog("CreateWindowEx Failed");
        return E_FAIL;
    }

    // 창을 활성화하고 현재 크기와 위치에 표시
    ShowWindow(this->hWnd, SW_SHOW);
    UpdateWindow(this->hWnd);

    mouse = new MouseManager(hWnd);
    keyboard = new KeyboardManager();
    
    SetCursorPos(centerScreenX + width / 2, centerScreenY + height / 2);

    return hr;
}

MouseManager* Window::GetMouse() const
{
    return this->mouse;
}

KeyboardManager* Window::GetKeyboard() const
{
    return this->keyboard;
}

HRESULT Window::RegisterWindow() const
{
    WNDCLASSEX wcx = {};
    wcx.hInstance = this->hInstance;
    wcx.lpszClassName = this->className;
    wcx.style = CS_VREDRAW | CS_HREDRAW; // 클라이언트 너비 변경 시 윈도우 전체를 다시 그림
    wcx.lpfnWndProc = WindowProc;

    wcx.cbSize = sizeof(WNDCLASSEX);
    wcx.hCursor = LoadCursor(NULL, IDC_ARROW);
    wcx.hIcon = LoadIcon(NULL, IDI_APPLICATION);

    if (!RegisterClassEx(&wcx))
        return E_FAIL;

    return S_OK;
}