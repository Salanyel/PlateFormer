#include "PhysicsEngine.h"


PhysicsEngine::PhysicsEngine(RenderWindow * window) : m_window(window)
{
	m_map = new Map("Assets/Maps/maps.xml");
}


PhysicsEngine::~PhysicsEngine()
{
	delete(m_map);
}

void PhysicsEngine::setCurrentState(PHYSIC_STATES newState)
{
	m_currentState = newState;
}
void PhysicsEngine::setWindow(RenderWindow * window)
{
	m_window = window;
}

bool PhysicsEngine::initEngine()
{
	switch (m_currentState)
	{
	case GAME_PHYSICS:
		if (!m_map->loadMap())
			return false;
		m_map->display();
		break;

	default:
		return false;
	}

	return true;
}

Map * PhysicsEngine::getMap()
{
	return m_map;
}
