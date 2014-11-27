#ifndef GRAPHICSCOMPONENT_H
#define GRAPHICSCOMPONENT_H

#include "Component.h"

enum GraphicShapeTypes { GST_Plane = 0, GST_Sphere, GST_Cube };
enum Colours { RED = 0, ORANGE, YELLOW, GREEN, BLUE, VIOLET };

class GraphicsComponent : public Component
{
public:
	typedef struct GVector3f 
	{
		float x;
		float y;
		float z;
	};

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

	void SetDimensions(float _w, float _d, float _h)
	{ m_Width = _w; m_Depth = _d; m_Height = _h; }

	void SetColour(float _r, float _g, float _b)
	{ colour.x = _r; colour.y = _g; colour.z = _b; }
	void SetRandomColour();
	GVector3f GetColour()
	{ return colour; } 

	void DrawPlane();
	void DrawSphere();
	void DrawPrism();

private:
	double m_Radius;
	float m_Height;
	float m_Width;
	float m_Depth;

	GVector3f colour;
protected:
};

#endif