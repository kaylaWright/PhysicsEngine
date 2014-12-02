#include <iostream>
#include <GL\include\glut.h>
#include "../SDL2/include/SDL.h"
#include "../SDL2/include/SDL_opengl.h"
#include "PhysicsManager.h"
#include "Entity.h"
#include "Component.h"
#include "PhysicsComponent.h"
#include "GraphicsComponent.h"

#include "../BulletDynamics/Dynamics/btRigidBody.h"

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

void LoadLevelOne();
void LoadLevelTwo();
void ClearLevel();

void MovePaddle();
void MoveBall();
void DisplayText(std::string _str);

//game objects.
Entity paddle;
Entity ball;

Entity obstacleOne;
Entity obstacleTwo;

int currLevel;

int main(int argc, char **argv)
{
	srand(time(NULL));

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
	window = SDL_CreateWindow(	"Totally Not Just Falling Stuff : Not Runbow Either",
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

	LoadLevelOne();
	currLevel = 1;

	DWORD prevTime = GetCurrentTime();

	// Main loop
	do
	{
		while (SDL_PollEvent(&curEvent))
		{
			HandleEvents(&curEvent);
		}
		
		//time calcs.
		DWORD currTime = GetCurrentTime();
		float dt = (currTime - prevTime) * 0.001;
		Update(dt);
		prevTime = currTime;

		Render(window);

	} while (game_running);

	physicsManager->Shutdown();
	return 0;
}

void InitGL()
{
	glClearColor(0, 0, 0, 1);
	glViewport(0, 0, screenWidth, screenHeight);
	glShadeModel(GL_SMOOTH);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glEnable(GL_DEPTH_TEST);

}

void LoadLevelOne()
{
	//no obstacles; just a paddle and a ball.
	//paddle.
	Entity::EVector3f pos;
	pos.x = 0.0f;
	pos.y = -15.0f;
	pos.z = 0.0f;
	paddle.SetPosition(pos);

	PhysicsComponent* pc = new PhysicsComponent();
	pc->SetOwner(&paddle);
	pc->SetDimensions(3.5f, 2.0f, 1.5f);
	pc->SetMass(1.0f);
	pc->Init(RBST_Prism);
	pc->GetRigidBody()->setLinearFactor(btVector3(1.0f, 0.0f, 0.0f));
	pc->GetRigidBody()->setLinearVelocity(btVector3(5.0f, 0.0f, 0.0f));
	//pc->GetRigidBody()->setCollisionFlags(btCollisionObject::CF_KINEMATIC_OBJECT);
	//pc->GetRigidBody()->setActivationState(DISABLE_DEACTIVATION);

	paddle.AddComponent("physics", pc);

	GraphicsComponent* gc = new GraphicsComponent(GST_Cube);
	gc->Init();
	gc->SetRandomColour();
	gc->SetDimensions(3.5f, 2.0f, 1.5f);
	paddle.AddComponent("graphics", gc);

	entities.push_back(paddle);

	//ball
	pos.y = 15.0f;
	ball.SetPosition(pos);

	pc = new PhysicsComponent();
	pc->SetOwner(&ball);
	pc->SetRadius(1.0f);
	pc->SetMass(2.0f);
	pc->Init(RBST_Sphere);
	pc->GetRigidBody()->setGravity(btVector3(0.0f, 0.0f, 0.0f));
	//always active. 
	pc->GetRigidBody()->setActivationState(4);
	ball.AddComponent("physics", pc);

	gc = new GraphicsComponent(GST_Sphere);
	gc->Init();
	gc->SetRandomColour();
	gc->SetDimensions(2.5f, 0.75f, 1.5f);
	gc->SetRadius(1.0f);
	ball.AddComponent("graphics", gc);
	ball.hasBeenHit = false;

	entities.push_back(ball);
}

void LoadLevelTwo()
{
	//paddle and ball required.
	LoadLevelOne();

	///two obstacles and paddle/ball -> can roll over paddle probably.
	Entity::EVector3f pos;
	pos.x = 10.0f;
	pos.y = 5.0f;
	pos.z = 0.0f;
	obstacleOne.SetPosition(pos);

	PhysicsComponent* pc = new PhysicsComponent();
	pc->SetOwner(&obstacleOne);
	pc->SetRadius(4.5f);
	pc->SetMass(0.0f);
	pc->Init(RBST_Sphere);
	pc->GetRigidBody()->setCollisionFlags(1);
	obstacleOne.AddComponent("physics", pc);

	GraphicsComponent* gc = new GraphicsComponent(GST_Sphere);
	gc->Init();
	gc->SetRandomColour();
	gc->SetRadius(4.5f);
	obstacleOne.AddComponent("graphics", gc);

	entities.push_back(obstacleOne);

	//obstacle two.
	pos.x = -5.0f;
	pos.y = 0.0f;
	pos.z = 0.0f;
	obstacleTwo.SetPosition(pos);

	pc = new PhysicsComponent();
	pc->SetOwner(&obstacleTwo);
	pc->SetDimensions(5.0f, 4.0f, 1.0f);
	pc->SetMass(0.0f);
	pc->Init(RBST_Prism);
	pc->GetRigidBody()->setCollisionFlags(1);
	obstacleTwo.AddComponent("physics", pc);

	gc = new GraphicsComponent(GST_Cube);
	gc->Init();
	gc->SetDimensions(5.0f, 4.0f, 1.0f);
	gc->SetRandomColour();
	obstacleTwo.AddComponent("graphics", gc);

	entities.push_back(obstacleTwo);
}

void ClearLevel()
{
	//empty all entities and delete them from the scene.
	entities.clear();
}

void HandleEvents(SDL_Event* curEvent)
{
	Component* temp;

	switch (curEvent->type)
	{
	case SDL_QUIT:
		game_running = false;
		break;
	case SDL_KEYDOWN:
		switch (curEvent->key.keysym.sym)
		{
		//move ball left.
		case SDLK_a:
		case SDLK_LEFT:
			temp = dynamic_cast<PhysicsComponent*>(ball.GetComponentByKey("physics"));
			dynamic_cast<PhysicsComponent*>(temp)->GetRigidBody()->applyCentralForce(btVector3(-10.0f, 0.0f, 0.0f));
				//applyForce(btVector3(-5.0f, 0.0f, 0.0f), dynamic_cast<PhysicsComponent*>(temp)->GetRigidBody()->getCenterOfMassPosition());
			break;
		//move ball right.
		case SDLK_d:
		case SDLK_RIGHT:
			temp = dynamic_cast<PhysicsComponent*>(ball.GetComponentByKey("physics"));
			dynamic_cast<PhysicsComponent*>(temp)->GetRigidBody()->applyCentralForce(btVector3(10.0f, 0.0f, 0.0f));
			break;
		default:
			break;
		}
		break;
	case SDL_KEYUP:
		switch (curEvent->key.keysym.sym)
		{
		//debug.
		case SDLK_p:
			PhysicsManager::GetInstance()->SetDebug( !PhysicsManager::GetInstance()->IsDebugOn() );
			break;
		case SDLK_q:
			if(currLevel > 2)
			{
				ClearLevel();
				LoadLevelOne();
			}
			break;
		//drop the ball.
		case SDLK_SPACE:
		case SDLK_DOWN:
			temp = dynamic_cast<PhysicsComponent*>(ball.GetComponentByKey("physics"));
			dynamic_cast<PhysicsComponent*>(temp)->GetRigidBody()->setGravity(btVector3(0.0f, -9.7f, 0.0f));
			break;
		case SDLK_w:
		case SDLK_UP:
			//change the ball colour.
			temp = dynamic_cast<GraphicsComponent*>(ball.GetComponentByKey("graphics"));
			dynamic_cast<GraphicsComponent*>(temp)->CycleThroughColours();
			break;
		//exit.
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

	if(ball.hasBeenHit)
	{
		ClearLevel();
		
		if(currLevel == 1)
		{
			LoadLevelTwo();
			
		}
		else
		{
			DisplayText("Press Q to play again.");
			//game over. Press Q to load level one again.
			
		}

		currLevel++;
	}

	MovePaddle();
	MoveBall();
}

void MovePaddle()
{
	btRigidBody* ptemp = dynamic_cast<PhysicsComponent*>(paddle.GetComponentByKey("physics"))->GetRigidBody();

	//make sure the speed is constant. 
	if(ptemp->getLinearVelocity().getX() < 0.0f && ptemp->getLinearVelocity().getX() > -5.0f)
	{
		ptemp->setLinearVelocity(btVector3(-5.0f, 0.0f, 0.0f));
	}

	if(ptemp->getLinearVelocity().getX() > 0.0f && ptemp->getLinearVelocity().getX() < 5.0f)
	{
		ptemp->setLinearVelocity(btVector3(5.0f, 0.0f, 0.0f));
	}

	//check paddle position. if it exceeds a certain x value, invert the linear velocity on the physics component and change the colour.
	//oppose it if it is too low on the x value; still change colour.
	if(paddle.GetPosition().x > 15.0f || paddle.GetPosition().x < -15.0f )
	{
		ptemp->setLinearVelocity(-(ptemp->getLinearVelocity()));

		GraphicsComponent* gtemp = dynamic_cast<GraphicsComponent*>(paddle.GetComponentByKey("graphics"));
		gtemp->SetRandomColour();
	}
}

void MoveBall()
{
	PhysicsComponent* ptemp = dynamic_cast<PhysicsComponent*>(ball.GetComponentByKey("physics"));

		//ball related.
	if(ball.GetPosition().y < -25)
	{
		
		btTransform t = ptemp->GetRigidBody()->getCenterOfMassTransform();
		t.setOrigin(btVector3(0.0f, 15.0f, 0.0f));
		ptemp->GetRigidBody()->setCenterOfMassTransform(t);
		ptemp->GetRigidBody()->setLinearVelocity(btVector3(0.0f, 0.0f, 0.0f));
		ptemp->GetRigidBody()->setGravity(btVector3(0.0f, 0.0f, 0.0f));
	}

	//basically stops ball from going offscreen.
	if(ball.GetPosition().x < -15 || ball.GetPosition().x > 15)
	{
		ptemp->GetRigidBody()->setLinearVelocity(-(ptemp->GetRigidBody()->getLinearVelocity()));
	}
}

void DisplayText(std::string _str)
{
	int lengthOfQuote;

	glPushMatrix();

	glTranslatef(screenWidth / 2 - 50, screenHeight / 2 - 50, 0.0f);

	lengthOfQuote = (int)strlen(_str.c_str());
	for (int i = 0; i < lengthOfQuote; i++)
	{
		glPushMatrix();

		glTranslatef(-(lengthOfQuote*37), -(i*200), 0.0);
		glColor3f(0.5f, 0.5f, 0.5f);
		glutStrokeCharacter(GLUT_STROKE_ROMAN, _str.c_str()[i]);
		std::cout <<  _str.c_str()[i] << std::endl;

		glPopMatrix();
	}

	glPopMatrix();

	std::cout << _str << std::endl;
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