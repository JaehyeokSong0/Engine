#include <stdafx.h>
#include "KeyboardManager.h"

KeyboardManager::KeyboardManager()
{
	keyboard = make_unique<Keyboard>();
}

Keyboard::State KeyboardManager::GetKeyboardState()
{
	return keyboard->GetState();
}