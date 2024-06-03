#include <stdafx.h>
#include "Object.h"
#include "../Component/Component.h"

Object::Object()
{
	transform = new Transform(XMFLOAT3_ZERO, XMFLOAT3_ZERO);
	components.clear();
}

Object::~Object()
{
	if (transform != nullptr)
	{
		delete transform;
		transform = nullptr;
	}

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

void Object::Create(const Transform& transform)
{
	//this->transform = transform;
	this->transform->position = transform.position;
	this->transform->rotation = transform.rotation;
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
			// (TODO) RTTI - need all hierarchy information
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

bool Object::GetComponent(const ComponentClass type, Component* outComponent)
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