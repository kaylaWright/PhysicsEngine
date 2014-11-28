#include "PhysicsManager.h"

#include "btBulletDynamicsCommon.h"
#include "PhysicsComponent.h"

PhysicsManager* PhysicsManager::m_Instance = nullptr;
bool ContactProcCallback(btManifoldPoint& cp, void* body0, void* body1)
{
	return true;
}

btScalar ContactCallback::addSingleResult(btManifoldPoint& cp,	const btCollisionObjectWrapper* colObj0Wrap,int partId0,int index0,const btCollisionObjectWrapper* colObj1Wrap,int partId1,int index1)
{
		const btCollisionObject* colObj = colObj0Wrap->getCollisionObject();
		PhysicsComponent* physComp = static_cast<PhysicsComponent*>(colObj->getUserPointer());
		
		if(physComp)
			physComp->OnAddSingleResult(cp,partId0,index0,colObj1Wrap,partId1,index1);

		return 0;
}

void PhysicsManager::Init()
{
	///collision configuration contains default setup for memory, collision setup
	m_collisionConfiguration = new btDefaultCollisionConfiguration();
	//m_collisionConfiguration->setConvexConvexMultipointIterations();

	///use the default collision dispatcher. For parallel processing you can use a diffent dispatcher (see Extras/BulletMultiThreaded)
	m_dispatcher = new	btCollisionDispatcher(m_collisionConfiguration);

	m_broadphase = new btDbvtBroadphase();

	///the default constraint solver. For parallel processing you can use a different solver (see Extras/BulletMultiThreaded)
	btSequentialImpulseConstraintSolver* sol = new btSequentialImpulseConstraintSolver;
	m_solver = sol;

	m_dynamicsWorld = new btDiscreteDynamicsWorld(m_dispatcher, m_broadphase, m_solver, m_collisionConfiguration);

	m_dynamicsWorld->setGravity(btVector3(0, -10.0, 0));

	gContactProcessedCallback = &ContactProcCallback;
}

void PhysicsManager::Shutdown()
{
	// Clean up behind ourselves like good little programmers
   /* delete m_broadphase;
    delete m_dispatcher;
    delete m_solver;
    delete m_collisionConfiguration;
    delete m_dynamicsWorld;*/
}

void PhysicsManager::Update(float deltaTime)
{
	m_dynamicsWorld->stepSimulation(deltaTime, 10);
	m_dynamicsWorld->contactTest(m_dynamicsWorld->getCollisionObjectArray()[0],m_ContactCallback);
}

void PhysicsManager::AddPhysicsComponent(PhysicsComponent* physComp)
{
    m_dynamicsWorld->addRigidBody(physComp->GetRigidBody());
}

void PhysicsManager::RemovePhysicsComponent(PhysicsComponent* physComp)
{
	m_dynamicsWorld->removeRigidBody(physComp->GetRigidBody());
}