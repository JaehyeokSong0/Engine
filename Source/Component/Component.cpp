#include <stdafx.h>
#include "Component.h"

Component::Component(const ComponentClass& type)
{
	this->type = type;
}

void Component::Update()
{
}

void Component::Start()
{
}

const ComponentClass Component::GetComponentType() const
{
	return type;
}