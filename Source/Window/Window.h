#pragma once
#include "../InputSystem/InputSystem.h"

class Window
{
public:
	Window() = default;
	~Window();

	HWND GetHandle() const;
	HINSTANCE GetInstance() const;
	LPCTSTR GetClassName() const;
	HRESULT Initialize(
		HINSTANCE hInstance, LPCTSTR className, LPCTSTR windowName,
		int width, int height
	);

	MouseManager* GetMouse() const;
	KeyboardManager* GetKeyboard() const;
private:
	HINSTANCE hInstance;
	HWND hWnd;
	LPCTSTR className; // LPCTSTR : long pointer constant t_string
	LPCTSTR windowName;
	int width;
	int height;
	
	MouseManager* mouse = nullptr;
	KeyboardManager* keyboard = nullptr;

	static LRESULT CALLBACK WindowProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam);
	HRESULT RegisterWindow() const;
};
