#ifndef GRAPHICSCOMPONENT_H
#define GRAPHICSCOMPONENT_H

#include "Component.h"

enum GraphicShapeTypes { GST_Plane = 0, GST_Sphere, GST_Cube };
enum Colours { eRED = 0, eORANGE, eYELLOW, eGREEN, eBLUE, eVIOLET };

class GraphicsComponent : public Component
{
public:
	typedef struct GVector3f 
	{
		GVector3f(float _x = 0.0f, float _y = 0.0f, float _z = 0.0f)
		{ x = _x; y = _y; z = _z; }
		float x;
		float y;
		float z;
	};

	const GVector3f RED;
	const GVector3f ORANGE;
	const GVector3f YELLOW;
	const GVector3f GREEN;
	const GVector3f BLUE;
	const GVector3f VIOLET;

	GraphicShapeTypes componentType;
	Colours currentColour;

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

	void SetColour(GVector3f _new)
	{ colour.x = _new.x; colour.y = _new.y; colour.z = _new.z; }
	GVector3f GetColour()
	{ return colour; } 
	void SetRandomColour();
	void CycleThroughColours();

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