#include "PhysicsComponent.h"
#include "PhysicsManager.h"
#include "btBulletDynamicsCommon.h"
#include <iostream>
#include "Entity.h"

using namespace std;

void PhysicsComponent::Init(RigidBodyShapeTypes type)
{
	Component::Init();
	switch (type)
	{
	case RBST_Prism:
		CreatePrism();
		break;
	case RBST_Plane:
		CreatePlane();
		break;
	case RBST_Sphere:
		CreateSphere();
		break;
	default:
		break;
	}
}

void PhysicsComponent::CreateSphere()
{
	btCollisionShape* sphereShape = new btSphereShape(m_Radius);
	
	Entity* entOwner = GetOwner();
	Entity::EVector3f pos = entOwner->GetPosition();

	btDefaultMotionState* fallMotionState =
                new btDefaultMotionState(btTransform(btQuaternion(0, 0, 0, 1), btVector3(pos.x, pos.y, pos.z)));

	btScalar mass = m_Mass;
        btVector3 fallInertia(0, 0, 0);
        sphereShape->calculateLocalInertia(mass, fallInertia);

	btRigidBody::btRigidBodyConstructionInfo fallRigidBodyCI(mass, fallMotionState, sphereShape, fallInertia);
        m_rigidBody = new btRigidBody(fallRigidBodyCI);

		m_rigidBody->setUserPointer(this);
		//add physicsbody to world
		PhysicsManager::GetInstance()->AddPhysicsComponent(this);
}

void PhysicsComponent::CreatePrism()
{
	btCollisionShape* prismShape = new btBoxShape(btVector3(m_Width, m_Height, m_Depth));

	Entity* entOwner = GetOwner();
	Entity::EVector3f pos = entOwner->GetPosition();

	btDefaultMotionState* fallMotionState =  new btDefaultMotionState(btTransform(btQuaternion(0, 0, 0, 1), btVector3(pos.x, pos.y, pos.z)));

	btScalar mass = m_Mass; 
	btVector3 fallInertia(0, 0, 0);
	prismShape->calculateLocalInertia(mass, fallInertia);

	btRigidBody::btRigidBodyConstructionInfo fallRigidBodyCI(mass, fallMotionState, prismShape, fallInertia);
	m_rigidBody = new btRigidBody(fallRigidBodyCI);

	m_rigidBody->setUserPointer(this);

	PhysicsManager::GetInstance()->AddPhysicsComponent(this);
}

void PhysicsComponent::CreatePlane()
{
	btCollisionShape* planeShape = new btStaticPlaneShape(btVector3(0,1,0),1.0f);
	
	btDefaultMotionState* planeMotionState = new btDefaultMotionState(btTransform(btQuaternion(0, 0, 0, 1), btVector3(0, -1, 0)));
	

	btRigidBody::btRigidBodyConstructionInfo planeRigidBodyCI(0, planeMotionState, planeShape, btVector3(0, 0, 0));

    btRigidBody* planeRigidBody = new btRigidBody(planeRigidBodyCI);

	m_rigidBody = planeRigidBody;

	//add physicsbody to world
		PhysicsManager::GetInstance()->AddPhysicsComponent(this);
}

void PhysicsComponent::Shutdown()
{
	//remove rigidBody from physics world
	PhysicsManager::GetInstance()->RemovePhysicsComponent(this);
}

void PhysicsComponent::Update(float DeltaTime)
{
	btVector3 worldPos = m_rigidBody->getWorldTransform().getOrigin();
	Entity::EVector3f pos;
	pos.x = worldPos.getX();
	pos.y = worldPos.getY();
	pos.z = worldPos.getZ();

	m_Owner->SetPosition(pos);

	if(PhysicsManager::GetInstance()->IsDebugOn())
	{
		DebugPrint();
	}
}



void PhysicsComponent::OnAddSingleResult(btManifoldPoint& cp,int partId0,int index0,const btCollisionObjectWrapper* collidedObjWrap,int collidedObjPartId,int collidedObjIndex)
{
	const btCollisionObject* colObj = collidedObjWrap->getCollisionObject();
	PhysicsComponent* physComp = static_cast<PhysicsComponent*>(colObj->getUserPointer());
	if(physComp)
	{
		Entity* entOwner = physComp->GetOwner();
		//entOwner->OnHit();
	}
}

void PhysicsComponent::DebugPrint()
{
	if(m_rigidBody)
	{
		btVector3 worldPos = m_rigidBody->getWorldTransform().getOrigin();
		cout << "Rigid Body Position X:" << worldPos.getX() 
			<< " Y:" << worldPos.getY() << " Z:" << worldPos.getZ() << endl; 
	}
	else
	{
		cout << "Rigid body not instatiated" << endl;
	}
}