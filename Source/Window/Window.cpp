#include <stdafx.h>
#include "Window.h"

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

    this->hWnd = CreateWindowEx(
        WS_OVERLAPPED,
        className,
        windowName,
        WS_CAPTION | WS_MINIMIZEBOX | WS_SYSMENU, 
        0, 0,
        width, height,
        nullptr,
        nullptr,
        this->hInstance,
        nullptr);

    if (this->hWnd == nullptr)
    {
        DebugLog("CreateWindowEx Failed");
        return E_FAIL;
    }

    // â�� Ȱ��ȭ�ϰ� ���� ũ��� ��ġ�� ǥ��
    ShowWindow(this->hWnd, SW_SHOW);
    UpdateWindow(this->hWnd);

    return hr;
}

HRESULT Window::RegisterWindow() const
{
    WNDCLASSEX wcx = {};
    wcx.hInstance = this->hInstance;
    wcx.lpszClassName = this->className;
    wcx.style = CS_VREDRAW | CS_HREDRAW; // Ŭ���̾�Ʈ �ʺ� ���� �� ������ ��ü�� �ٽ� �׸�
    wcx.lpfnWndProc = WindowProc;

    wcx.cbSize = sizeof(WNDCLASSEX);
    wcx.hCursor = LoadCursor(NULL, IDC_ARROW);
    wcx.hIcon = LoadIcon(NULL, IDI_APPLICATION);

    if (!RegisterClassEx(&wcx))
        return E_FAIL;

    return S_OK;
}