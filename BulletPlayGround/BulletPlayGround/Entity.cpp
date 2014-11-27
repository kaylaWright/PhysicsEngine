#include "Entity.h"
#include "Component.h"


void Entity::AddComponent(const std::string _name, Component* component)
{
	if(component->GetOwner() == nullptr)
		component->SetOwner(this);

	m_Components[_name] = component;

	//m_Components.push_back(component);
}

Component* Entity::GetComponentByKey(std::string _key)
{
	map_IT temp = m_Components.find(_key);
	
	if(temp != m_Components.end())
		return temp->second;
	else
		return NULL;
}

void Entity::RemoveComponent(Component* component)
{
	for(map_IT it = m_Components.begin(); it != m_Components.end(); ++it)
	{
		if((*it).second == component)
		{
			it = m_Components.erase(it);
			break;
		}
	}

	//for(std::vector<Component*>::iterator it = m_Components.begin(); it != m_Components.end(); ++it)
	//{
	//	if( (*it) == component)
	//	{
	//		it = m_Components.erase(it);
	//		break;
	//	}
	//}
}

void Entity::Update(float deltaTime) 
{
	for(map_IT it = m_Components.begin(); it != m_Components.end(); ++it)
	{
		(*it).second->Update(deltaTime);
	}

	//for(std::vector<Component*>::iterator it = m_Components.begin(); it != m_Components.end(); ++it)
	//{
	//	(*it)->Update(deltaTime);
	//}
}

void Entity::Render()
{
	for(map_IT it = m_Components.begin(); it != m_Components.end(); ++it)
	{
		(*it).second->Render();
	}

	//for(std::vector<Component*>::iterator it = m_Components.begin(); it != m_Components.end(); ++it)
	//{
	//	(*it)->Render();
	//}
}
