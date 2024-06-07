 #pragma once

struct Transform;
class Component;
enum class ComponentClass;

class Object
{
public:
	Object();
	~Object();

	void Create();
	void Create(const Transform& transform);
	void Update(); // Check current components and update object's status

	bool AddComponent(Component* newComponent);
	bool RemoveComponent(Component* removeComponent);
	bool GetComponent(const ComponentClass type, Component* outComponent = nullptr);

private:
	Transform* transform;
	vector<Component*> components;
};