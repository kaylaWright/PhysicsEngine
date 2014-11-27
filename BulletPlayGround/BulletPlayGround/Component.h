#ifndef COMPONENT_H
#define COMPONENT_H

class Entity;

class Component
{
public:
	Component() : m_Owner(nullptr) {}
	virtual ~Component() {}

	virtual void Init() {}
	virtual void Shutdown() {}

	virtual void Update(float deltaTime) {}
	virtual void Render() {}

	void SetOwner(Entity* owner) {m_Owner = owner;}
	Entity* GetOwner() const {return m_Owner;}
protected:
	Entity* m_Owner;
};

#endif