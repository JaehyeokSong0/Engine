#pragma once

#include "../Component/Component.h"

class Object
{
public:
	Object();
	~Object();

	void Create();
	void Create(const Transform& transform);
	
	void SetTransform(const Transform& transform);
	Transform GetTransform() const;

	void Update(); // Check current components and update object's status

	bool AddComponent(Component* newComponent);
	bool RemoveComponent(Component* removeComponent);
	Component* GetComponent(const ComponentClass type);

	void Destroy();

private:
	Transform transform;
	vector<Component*> components;
};