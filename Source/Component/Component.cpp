#include <stdafx.h>
#include "Component.h"

Component::Component(const ComponentClass type)
{
	this->type = type;
}

const ComponentClass Component::GetComponentType() const
{
	return type;
}