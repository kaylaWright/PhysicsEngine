#include <iostream>
#include <GL\include\glut.h>
#include "../SDL2/include/SDL.h"
#include "../SDL2/include/SDL_opengl.h"
#include "PhysicsManager.h"
#include "Entity.h"
#include "Component.h"
#include "PhysicsComponent.h"
#include "GraphicsComponent.h"

// Game Loop variables
bool game_running = true;

std::vector<Entity> entities;
PhysicsManager* physicsManager = nullptr;

// Screen size
int screenWidth = 640;
int screenHeight = 480;

// Function prototypes
void InitGL();
void HandleEvents(SDL_Event* curEvent);
void Update(float dt);
void Render(SDL_Window* window);

float FRAMERATE = 1.0f/60.0f;

int main(int argc, char **argv)
{
	SDL_Init(SDL_INIT_EVERYTHING);

	SDL_Window* window;
	SDL_Event curEvent;
	SDL_GLContext glContext;

	// Set our base SDL attributes.
	SDL_GL_SetAttribute(SDL_GL_RED_SIZE, 8);
	SDL_GL_SetAttribute(SDL_GL_GREEN_SIZE, 8);
	SDL_GL_SetAttribute(SDL_GL_BLUE_SIZE, 8);
	SDL_GL_SetAttribute(SDL_GL_ALPHA_SIZE, 8);
	SDL_GL_SetAttribute(SDL_GL_BUFFER_SIZE, 8);
	SDL_GL_SetAttribute(SDL_GL_DEPTH_SIZE, 8);
	SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);

	// Create our SDL window.
	window = SDL_CreateWindow(	"Physics Playground",
		SDL_WINDOWPOS_UNDEFINED,
		SDL_WINDOWPOS_UNDEFINED,
		screenWidth, screenHeight,
		SDL_WINDOW_RESIZABLE | SDL_WINDOW_OPENGL);

	if (!window)
	{
		std::cout << "Couldn't create window: " << SDL_GetError() << std::endl;
		return 0;
	}

	// Create our openGL context with our window.
	glContext = SDL_GL_CreateContext(window);

	if (!glContext)
	{
		std::cout << "Couldn't create context: " << SDL_GetError() << std::endl;
		return 0;
	}

	// Init openGL
	InitGL();

	physicsManager = new PhysicsManager();
	physicsManager->Init();

	/*Entity ent;

	PhysicsComponent* pc = new PhysicsComponent();
	pc->SetOwner(&ent);
	pc->Init(PhysicsComponent::RBST_Plane);
	ent.AddComponent(pc);
	entities.push_back(ent);*/

	Entity ent2;
	Entity::EVector3f pos;
	pos.x = 0.0f;
	pos.y = 15.0f;
	pos.z = 0.0f;
	ent2.SetPosition(pos);

	PhysicsComponent* pc = new PhysicsComponent();
	pc->SetOwner(&ent2);
	pc->SetRadius(1.0f);
	pc->Init(PhysicsComponent::RBST_Sphere);
	ent2.AddComponent(pc);

	GraphicsComponent* gc = new GraphicsComponent(GST_Cube);
	gc->Init();
	gc->SetColour(0.0f, 1.0f, 0.0f);
	gc->SetHeight(1.5f);
	gc->SetDepth(0.75f);
	gc->SetWidth(2.5f);
	ent2.AddComponent(gc);

	entities.push_back(ent2);

	// Main loop
	do
	{
		while (SDL_PollEvent(&curEvent))
		{
			HandleEvents(&curEvent);
		}

		Update(FRAMERATE);
		
		Render(window);

	} while (game_running);

	pc->Shutdown();
	physicsManager->Shutdown();
	return 0;
}

void InitGL()
{
	glClearColor(1, 1, 1, 1);
	glViewport(0, 0, screenWidth, screenHeight);
	glShadeModel(GL_SMOOTH);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glEnable(GL_DEPTH_TEST);

}

void HandleEvents(SDL_Event* curEvent)
{
	switch (curEvent->type)
	{
	case SDL_QUIT:
		game_running = false;
		break;
	case SDL_KEYDOWN:
		switch (curEvent->key.keysym.sym)
		{
		default:
			break;
		}
		break;
	case SDL_KEYUP:
		switch (curEvent->key.keysym.sym)
		{
		case SDLK_d:
			PhysicsManager::GetInstance()->SetDebug( !PhysicsManager::GetInstance()->IsDebugOn() );
			break;
		case SDLK_ESCAPE:
			game_running = false;
			break;
		}
		break;
	default:
		break;
	}
}

void Update(float dt)
{
	physicsManager->Update(dt);
	for(std::vector<Entity>::iterator it = entities.begin(); it != entities.end(); ++it)
	{
		(*it).Update(dt);
	}
}

void Render(SDL_Window *window)
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(60, screenWidth / screenHeight, 0.1f, 250);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	// Should be change to camera class or similar.
	gluLookAt(0, 0, 30, 0, 0, 0, 0, 1, 0);
   
	for(std::vector<Entity>::iterator it = entities.begin(); it != entities.end(); ++it)
	{
        glPushMatrix();
		(*it).Render();
        glPopMatrix();
	}

	SDL_GL_SwapWindow(window);
}