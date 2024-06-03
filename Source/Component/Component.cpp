#include <stdafx.h>
#include "Component.h"

Component::Component(const wstring type)
{
	this->type = type;
}

const wstring Component::GetComponentType() const
{
	return type;
}
