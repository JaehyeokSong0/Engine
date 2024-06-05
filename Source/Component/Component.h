#pragma once

enum class ComponentClass
{
	MODEL,
};

class Component abstract
{
public:
	Component() = default;
	Component(const ComponentClass& type);
	virtual ~Component() = default;

	virtual void Start() = 0;
	virtual void Update() = 0;
	// All components must deallocate its allocated objects before its removal from Object.
	virtual void Destroy() = 0;

	const ComponentClass GetComponentType() const;

protected:
	ComponentClass type; // Every component need its name
};