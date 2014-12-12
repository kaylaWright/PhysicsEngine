#ifndef PHYSICSCOMPONENT_H
#define PHYSICSCOMPONENT_H

#include "Component.h"
#include "../BulletCollision/CollisionDispatch/btCollisionWorld.h"

class btRigidBody;

enum RigidBodyShapeTypes { RBST_Plane = 0, RBST_Sphere, RBST_Prism };

class PhysicsComponent : public Component
{
public:
	PhysicsComponent() : m_shapeType(RBST_Plane) {}
	 ~PhysicsComponent() 
	 { delete m_rigidBody; }

	void Init(RigidBodyShapeTypes type);
	void Shutdown();

	virtual void Update(float deltaTime);

	virtual void OnContactProcCallback(btManifoldPoint& _mani, PhysicsComponent* _collidedObject);
	virtual void OnAddSingleResult(btManifoldPoint& cp,int partId0,int index0,const btCollisionObjectWrapper* collidedObjWrap,int collidedObjPartId,int collidedObjIndex);

	void DebugPrint();

	btRigidBody* GetRigidBody() const {return m_rigidBody;}

	void SetShapeType(RigidBodyShapeTypes type) { m_shapeType = type;}
	RigidBodyShapeTypes GetShapeType() const { return m_shapeType; }

	float GetHeight() const { return m_Height;}
	void SetHeight(float height) {m_Height = height;}

	float GetWidth() const { return m_Width;}
	void SetWidth(float width) {m_Width = width;}

	float GetDepth() const { return m_Depth;}
	void SetDepth(float _depth) {m_Depth = _depth;}

	void SetDimensions(float _w, float _d, float _h)
	{ m_Width = _w; m_Depth = _d; m_Height = _h; }

	double GetRadius() const { return m_Radius;}
	void SetRadius(double radius) {m_Radius = radius;}

	float GetMass() const 
	{ return m_Mass; }
	void SetMass(float _new)
	{ m_Mass = _new; }
private:
	void CreatePlane();
	void CreateSphere();
	void CreatePrism();

	double m_Radius;
	float m_Height;
	float m_Width;
	float m_Depth;
	float m_Mass;

	//physics variables
	btRigidBody* m_rigidBody;
	RigidBodyShapeTypes m_shapeType;
};

#endif