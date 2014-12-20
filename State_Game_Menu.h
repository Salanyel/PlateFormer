#pragma once
#include <iostream>
#include <stdio.h>
#include "State_Game_Base.h"
#include "GraphicsEngine.h"
#include "PhysicsEngine.h"
#include "CXBOXController.h"

using namespace sf;

class State_Game_Menu :
	public State_Game_Base
{
public:
	State_Game_Menu(RenderWindow * window);
	~State_Game_Menu();

	virtual bool initState(RenderWindow * window);
	virtual bool clearState();
	virtual void operate();
	virtual void processEvents(Event event);
	virtual void processEvents();

	GraphicsEngine * getGraphics();

protected :
	GraphicsEngine * m_graphics;
	CXBOXController * m_player;
	int m_menuFocused = 0;
};

