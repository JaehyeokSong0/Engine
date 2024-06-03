#pragma once
#include "../Component/Component.h"

class Object
{
public:
	Object();
	~Object();

	void Create();
	void Create(Transform transform);
	void Update(); // Check current components and update object's status

	bool AddComponent(Component* newComponent);
	bool RemoveComponent(Component* removeComponent);
	bool GetComponent(const wstring type, Component* outComponent = nullptr);

private:
	Transform transform;
	vector<Component*> components;
};