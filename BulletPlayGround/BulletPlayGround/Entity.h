#ifndef ENTITY_H
#define ENTITY_H

#include <vector>
class Component;
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

	void AddComponent(Component *component);

	void RemoveComponent(Component* component)
	{
		for(std::vector<Component*>::iterator it = m_Components.begin(); it != m_Components.end(); ++it)
		{
			if( (*it) == component)
			{
				it = m_Components.erase(it);
				break;
			}
		}
	}

	void Update(float deltaTime);
	void Render();

	EVector3f GetPosition() const {return m_Position;}
	void SetPosition(EVector3f pos) { m_Position = pos;}

	EVector3f GetDimensions() const
	{ return m_Dimensions; }
	void SetDimensions(float _x, float _y, float _z)
	{ m_Dimensions.x = _x; m_Dimensions.y = _y; m_Dimensions.z = _z; }
private:
	std::vector<Component*> m_Components;
	EVector3f m_Position;

	EVector3f m_Dimensions;
};


#endif