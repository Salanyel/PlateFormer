#pragma once

#include <SFML\Graphics.hpp>
#include "Map.h"

using namespace std;
using namespace sf;

enum PHYSIC_STATES
{
	MENU_PHYSICS,
	GAME_PHYSICS
};

class PhysicsEngine
{
public:
	PhysicsEngine(RenderWindow * window);
	~PhysicsEngine();

	void setCurrentState(PHYSIC_STATES newState);
	void setWindow(RenderWindow * window);
	bool initEngine();

	Map * getMap();

protected:
	RenderWindow * m_window;
	Map * m_map;
	PHYSIC_STATES m_currentState;
};

