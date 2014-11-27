#ifndef GRAPHICSCOMPONENT_H
#define GRAPHICSCOMPONENT_H

#include "Component.h"
#include "Math.h"

enum GraphicShapeTypes { GST_Plane = 0, GST_Sphere, GST_Cube };

class GraphicsComponent : public Component
{
public:
	
	GraphicShapeTypes componentType;

	GraphicsComponent(GraphicShapeTypes _type); 
	virtual ~GraphicsComponent() {}
	virtual void Init() {}
	virtual void Shutdown() {}

	virtual void Update(float deltaTime);
	virtual void Render();

	double GetRadius() const { return m_Radius;}
	void SetRadius(double radius) {m_Radius = radius;}

	float GetHeight() const { return m_Height;}
	void SetHeight(float height) {m_Height = height;}

	float GetWidth() const { return m_Width;}
	void SetWidth(float width) {m_Width = width;}

	float GetDepth() const { return m_Depth;}
	void SetDepth(float _depth) {m_Depth = _depth;}

	void SetColour(float _r, float _g, float _b)
	{ colour.x = _r; colour.y = _g; colour.z = _b; }
	Vector3 GetColour()
	{ return colour; } 

	void DrawPlane();
	void DrawSphere();
	void DrawPrism();

private:
	double m_Radius;
	float m_Height;
	float m_Width;
	float m_Depth;

	Vector3 colour;
protected:
};

#endif