#pragma once

class Component abstract
{
public:
	Component() = default;
	Component(const wstring type);
	virtual ~Component() = default;

	virtual void Update() = 0;
	// All components must deallocate its allocated objects before its removal from Object.
	virtual void Destroy() = 0;

	const wstring GetComponentType() const;

protected:
	wstring type; // Every component need its name
};