#pragma once
#include <Mouse.h>

// only have -1, 0, 1
struct MouseRelativeMove
{
	int x;
	int y;
};

class MouseManager
{
	const Mouse::Mode DEFAULT_MOUSE_MODE = Mouse::MODE_ABSOLUTE;
	
public:
	MouseManager(HWND hwnd);
	~MouseManager() = default;
	
	void SetMouseMode(Mouse::Mode mode);
	void AlterMouseMode();

	Mouse::State GetMouseState();
	MouseRelativeMove GetMouseDragState();

private:
	unique_ptr<DirectX::Mouse> mouse;
	Mouse::Mode currMode;

	// position
	int x = 0;
	int y = 0;
};