#include <stdafx.h>
#include "MouseManager.h"

MouseManager::MouseManager(HWND hwnd)
	: mouse(make_unique<Mouse>())
	, currMode(DEFAULT_MOUSE_MODE)
	, x(0) , y(0)
	, sensitivity(DEFAULT_SENSITIVITY)
{
	mouse->SetWindow(hwnd);
	SetMouseMode(currMode);
}

void MouseManager::SetMouseMode(Mouse::Mode mode)
{
	mouse->SetMode(mode);
}

void MouseManager::AlterMouseMode()
{
	currMode = (currMode == Mouse::MODE_ABSOLUTE) ? Mouse::MODE_RELATIVE : Mouse::MODE_ABSOLUTE;

	mouse->SetMode(currMode);
}

void MouseManager::SetSensitivity(float value)
{
	sensitivity = value;
}

float MouseManager::GetSensitivity()
{
	return sensitivity;
}

Mouse::State MouseManager::GetMouseState()
{
	return mouse->GetState();
}

// return x, y move state
MouseRelativeMove MouseManager::GetMouseDragState()
{
	int retX = 0, retY = 0;

	Mouse::State state = mouse->GetState();

	if (x != state.x)
	{
		retX = (x < state.x) ? 1 : -1;
		x = state.x;
	}

	if (y != state.y)
	{
		retY = (y > state.y) ? 1 : -1;
		y = state.y;
	}

	return MouseRelativeMove(retX, retY);
}
