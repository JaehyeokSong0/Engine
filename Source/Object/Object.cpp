#include <stdafx.h>
#include "Object.h"

Object::Object()
	: transform(Transform(XMFLOAT3_ZERO, XMFLOAT3_ZERO))
{
	components.clear();
}

Object::~Object()
{
	// Deallocate components
	for (auto component : components)
	{
		if (component != nullptr)
		{
			component->Destroy();

			delete component;
			component = nullptr;
		}
	}

	components.clear();
}

void Object::Create()
{
}

void Object::Create(Transform transform)
{
	this->transform = transform;
}

void Object::Update()
{
	for (auto component : components)
	{
		if (component != nullptr)
		{
			component->Update();
		}
	}
}

bool Object::AddComponent(Component* newComponent)
{
	// If object already has the component
	if (GetComponent(newComponent->GetComponentType()) == true)
		return false;

	components.push_back(newComponent);
	return true;
}

bool Object::RemoveComponent(Component* removeComponent)
{
	int index = 0;
	for (auto component : components)
	{
		if (component != nullptr)
		{
			if (component->GetComponentType() == removeComponent->GetComponentType())
			{
				component->Destroy();

				delete component;
				component = nullptr;

				components.erase(components.begin() + index);

				return true;
			}
		}
		index++;
	}

	return false;
}

bool Object::GetComponent(const wstring type, Component* outComponent)
{
	for (auto component : components)
	{
		if (component != nullptr)
		{
			if (type == component->GetComponentType())
			{
				outComponent = component;
				return true;
			}
		}
	}

	return false;
}