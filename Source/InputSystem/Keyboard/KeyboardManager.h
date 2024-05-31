#pragma once
#include <Keyboard.h>

class KeyboardManager
{
public:
	KeyboardManager();
	~KeyboardManager() = default;

	Keyboard::State GetKeyboardState();
	
private:
	unique_ptr<DirectX::Keyboard> keyboard;
};