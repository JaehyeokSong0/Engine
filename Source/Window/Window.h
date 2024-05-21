#pragma once

class Window
{
public:
	HWND GetHandle() const;
	HINSTANCE GetInstance() const;
	LPCTSTR GetClassName() const;
	HRESULT Initialize(
		HINSTANCE hInstance, LPCTSTR className, LPCTSTR windowName,
		int width, int height);

private:
	static LRESULT CALLBACK WindowProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam);
	HRESULT RegisterWindow() const;

	HINSTANCE hInstance;
	HWND hWnd;
	LPCTSTR className; // LPCTSTR : long pointer constant t_string
	LPCTSTR windowName;
	int width;
	int height;
};
