#ifndef PHYSICS_MANAGER_H
#define PHYSICS_MANAGER_H

#include <vector>
#include <LinearMath\btVector3.h>
#include "../BulletCollision/CollisionDispatch/btCollisionWorld.h"

class btBroadphaseInterface;
class btConstraintSolver;
class btCollisionDispatcher;
class btDefaultCollisionConfiguration;
class btDiscreteDynamicsWorld;
class btCollisionShape;
class btDefaultMotionState;
class btRigidBody;
class PhysicsComponent;

struct ContactCallback : public btCollisionWorld::ContactResultCallback
{
	virtual	btScalar addSingleResult(btManifoldPoint& cp,	const btCollisionObjectWrapper* colObj0Wrap,int partId0,int index0,const btCollisionObjectWrapper* colObj1Wrap,int partId1,int index1);
};

class PhysicsManager
{
public:

	PhysicsManager() : m_isDebugOn(false)
	{ 
		m_Instance = this; 
	}
	virtual ~PhysicsManager() {}
	
	void Init();
	void Shutdown();
	
	

	void AddPhysicsComponent(PhysicsComponent* physComp);
	void RemovePhysicsComponent(PhysicsComponent* physComp);

	void Update(float deltaTime);

	static PhysicsManager* GetInstance() 
	{
		return m_Instance;
	}

	void SetDebug(bool isOn) { m_isDebugOn = isOn; }
	bool IsDebugOn() const { return m_isDebugOn == true; }

private:
	btBroadphaseInterface*	m_broadphase;
	btCollisionDispatcher*	m_dispatcher;
	btConstraintSolver*	m_solver;
	btDefaultCollisionConfiguration* m_collisionConfiguration;
	btDiscreteDynamicsWorld* m_dynamicsWorld;

	static PhysicsManager* m_Instance;

	bool m_isDebugOn;
	ContactCallback m_ContactCallback;

	ContactProcessedCallback m_procCallback;

};

#endif