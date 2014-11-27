#include "Entity.h"
#include "Component.h"


void Entity::AddComponent(Component* component)
{
	if(component->GetOwner() == nullptr)
		component->SetOwner(this);

	m_Components.push_back(component);
}

void Entity::Update(float deltaTime) 
{
	for(std::vector<Component*>::iterator it = m_Components.begin(); it != m_Components.end(); ++it)
	{
		(*it)->Update(deltaTime);
	}
}

void Entity::Render()
{
	for(std::vector<Component*>::iterator it = m_Components.begin(); it != m_Components.end(); ++it)
	{
		(*it)->Render();
	}
}
