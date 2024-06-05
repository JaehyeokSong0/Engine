#pragma once
#include <Mouse.h>

// only have -1, 0, 1
struct MouseRelativeMove
{
	int x;
	int y;
};

const Mouse::Mode DEFAULT_MOUSE_MODE = Mouse::MODE_ABSOLUTE;
const float DEFAULT_SENSITIVITY = 0.1f;
	
class MouseManager
{
public:
	MouseManager(HWND hwnd);
	~MouseManager() = default;
	
	void SetMouseMode(Mouse::Mode mode);
	void AlterMouseMode();

	void SetSensitivity(float value);
	float GetSensitivity() const;

	Mouse::State GetMouseState() const;
	MouseRelativeMove GetMouseDragState();

private:
	unique_ptr<DirectX::Mouse> mouse;
	Mouse::Mode currMode;

	// position
	int x;
	int y;

	float sensitivity;
};