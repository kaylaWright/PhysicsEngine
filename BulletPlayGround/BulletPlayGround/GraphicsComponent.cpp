#include "GraphicsComponent.h"
#include "Entity.h"
#include <GL\include\glut.h>
#include "../SDL2/include/SDL.h"
#include "../SDL2/include/SDL_opengl.h"
#include <math.h>

GraphicsComponent::GraphicsComponent(GraphicShapeTypes _type) : RED(1.0f, 0.0f, 0.0f), ORANGE(1.0f, 0.5f, 0.0f), YELLOW(1.0f, 1.0f, 0.0f), 
																GREEN(0.0f, 1.0f, 0.0f), BLUE(0.0f, 0.0f, 1.0f), VIOLET(0.25f, 0.0f, 0.25f)
{
	
	componentType = _type;
}

void GraphicsComponent::DrawPrism()
{
	float ver[8][3] = 
	{
		{ -m_Width, -m_Height, m_Depth },
		{ -m_Width, m_Height, m_Depth },
		{ m_Width, m_Height, m_Depth },
		{ m_Width, -m_Height, m_Depth },
		{ -m_Width, -m_Height, -m_Depth },
		{ -m_Width, m_Height, -m_Depth },
		{ m_Width, m_Height, -m_Depth },
		{ m_Width, -m_Height, -m_Depth },
	};

	glColor3f(colour.x, colour.y, colour.z);

	glBegin(GL_QUADS);
		glVertex3fv(ver[0]);
		glVertex3fv(ver[3]);
		glVertex3fv(ver[2]);
		glVertex3fv(ver[1]);
	glEnd();

	glBegin(GL_QUADS);
		glVertex3fv(ver[2]);
		glVertex3fv(ver[3]);
		glVertex3fv(ver[7]);
		glVertex3fv(ver[6]);
	glEnd();

	glBegin(GL_QUADS);
		glVertex3fv(ver[0]);
		glVertex3fv(ver[4]);
		glVertex3fv(ver[7]);
		glVertex3fv(ver[3]);
	glEnd();

	glBegin(GL_QUADS);
		glVertex3fv(ver[1]);
		glVertex3fv(ver[2]);
		glVertex3fv(ver[6]);
		glVertex3fv(ver[5]);
	glEnd();

	glBegin(GL_QUADS);
		glVertex3fv(ver[4]);
		glVertex3fv(ver[5]);
		glVertex3fv(ver[6]);
		glVertex3fv(ver[7]);
	glEnd();

	glBegin(GL_QUADS);
		glVertex3fv(ver[0]);
		glVertex3fv(ver[1]);
		glVertex3fv(ver[5]);
		glVertex3fv(ver[4]);
	glEnd();
}

void GraphicsComponent::DrawPlane()
{
}

//void drawSphere(double radius, int nSlice, int nStack)
void GraphicsComponent::DrawSphere()
{
    double radius = m_Radius;
    int nSlice = 10;
    int nStack = 10;
    int i, j;
    double phi; //
    double theta; //long
    float p[31][31][3]; //Vertex
    float *p1,*p2,*p3,*p4;

    if(nSlice > 30) nSlice = 30;
    if(nStack > 30) nStack = 30;

	glColor3f(colour.x, colour.y, colour.z);

    //Vertex
    for(i = 0;i <= nSlice;i++)
    {   
        phi = 2.0 * M_PI * (double)i / (double)nSlice;
        for(j = 0;j <= nStack;j++)
        {   
            theta = M_PI * (double)j / (double)nStack;
            p[i][j][0] = (float)(radius * sin(theta) * cos(phi));//x
            p[i][j][1] = (float)(radius * sin(theta) * sin(phi));//y
            p[i][j][2] = (float)(radius * cos(theta));           //z
        }
    }

    //Top(j=0)
    for(i = 0;i < nSlice; i++)
    {
        p1 = p[i][0];     p2 = p[i][1];
        p3 = p[i+1][1]; 
        glBegin(GL_TRIANGLES);
        glNormal3fv(p1); glVertex3fv(p1);
        glNormal3fv(p2); glVertex3fv(p2);
        glNormal3fv(p3); glVertex3fv(p3);
        glEnd();
    }
    //Bottom
    j=nStack-1;
    for(i = 0;i < nSlice; i++)
    {
        p1 = p[i][j];     p2 = p[i][j+1];
        p3 = p[i+1][j]; 
        glBegin(GL_TRIANGLES);
        glNormal3fv(p1); glVertex3fv(p1);
        glNormal3fv(p2); glVertex3fv(p2);
        glNormal3fv(p3); glVertex3fv(p3);
        glEnd();
    }

    for(i = 0;i < nSlice;i++){
        for(j = 1;j < nStack-1; j++)
        {
            p1 = p[i][j];     p2 = p[i][j+1];
            p3 = p[i+1][j+1]; p4 = p[i+1][j];
            glBegin(GL_QUADS);
            glNormal3fv(p1); glVertex3fv(p1);
            glNormal3fv(p2); glVertex3fv(p2);
            glNormal3fv(p3); glVertex3fv(p3);
            glNormal3fv(p4); glVertex3fv(p4);
            glEnd();
        }
    }
}

void GraphicsComponent::Update(float deltaTime)
{
	
}

void GraphicsComponent::Render()
{
	glColor3f(1.0f,0.0f,0.0f);
    Entity::EVector3f pos = m_Owner->GetPosition();
    glTranslatef(pos.x,pos.y,pos.z);
	
	switch(componentType)
	{
	case GST_Sphere:
		DrawSphere();
		break;
	case GST_Cube:
		DrawPrism();
		break;
	case GST_Plane:
		DrawPlane();
		break;
	default:
		break;
	}

}

void GraphicsComponent::SetRandomColour()
{
	
	int rnd = rand() % 6;

	switch(rnd)
	{
	case eRED:
		currentColour = eRED;
		SetColour(RED);
		break;
	case eORANGE:
		currentColour = eORANGE;
		SetColour(ORANGE);
		break;
	case eYELLOW: 
		currentColour = eYELLOW;
		SetColour(YELLOW);
		break;
	case eGREEN:
		currentColour = eGREEN;
		SetColour(GREEN);
		break;
	case eBLUE:
		currentColour = eBLUE;
		SetColour(BLUE);
		break;
	case eVIOLET:
		currentColour = eVIOLET;
		SetColour(VIOLET);
		break;
	}
}

void GraphicsComponent::CycleThroughColours()
{
	switch(currentColour)
	{
	case eRED:
		currentColour = eORANGE;
		SetColour(ORANGE);
		break;
	case eORANGE:
		currentColour = eYELLOW;
		SetColour(YELLOW);
		break;
	case eYELLOW: 
		currentColour = eGREEN;
		SetColour(GREEN);
		break;
	case eGREEN:
		currentColour = eBLUE;
		SetColour(BLUE);
		break;
	case eBLUE:
		currentColour = eVIOLET;
		SetColour(VIOLET);
		break;
	case eVIOLET:
		currentColour = eRED;
		SetColour(RED);
		break;
	}

}