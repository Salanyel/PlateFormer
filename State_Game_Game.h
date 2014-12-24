#pragma once

#include <iostream>
#include <stdio.h>
#include "State_Game_Base.h"
#include "GraphicsEngine.h"
#include "PhysicsEngine.h"
#include "CXBOXController.h"

using namespace sf;

class State_Game_Game :
	public State_Game_Base
{
public:
	State_Game_Game(RenderWindow * window);
	~State_Game_Game();
	virtual int getStateStatus();

	virtual bool initState(RenderWindow * window);
	virtual bool clearState();
	virtual void operate();
	virtual void processEvents(Event event);
	virtual void processEvents();

	GraphicsEngine * getGraphics();
	PhysicsEngine * getPhysics();

protected:
	GraphicsEngine * m_graphics;
	PhysicsEngine * m_physics;
	CXBOXController * m_player;
	int STATE_CHANGE = 0;
};