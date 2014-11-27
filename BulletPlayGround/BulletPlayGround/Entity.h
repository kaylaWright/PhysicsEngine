#ifndef ENTITY_H
#define ENTITY_H

#include <unordered_map>
#include <string>

class Component;

typedef std::unordered_map<std::string, Component*>::iterator map_IT;

class Entity 
{
public:

	typedef struct EVector3f 
	{
		float x;
		float y;
		float z;
	};

	Entity() {}
	~Entity() {}

	void AddComponent(const std::string _name, Component* component);
	Component* GetComponentByKey(std::string _key);
	void RemoveComponent(Component* component);

	void Update(float deltaTime);
	void Render();

	EVector3f GetPosition() const {return m_Position;}
	void SetPosition(EVector3f pos) { m_Position = pos;}

	EVector3f GetDimensions() const
	{ return m_Dimensions; }
	void SetDimensions(float _x, float _y, float _z)
	{ m_Dimensions.x = _x; m_Dimensions.y = _y; m_Dimensions.z = _z; }
private:
	std::unordered_map<std::string, Component*> m_Components;
	EVector3f m_Position;

	EVector3f m_Dimensions;
};


#endif