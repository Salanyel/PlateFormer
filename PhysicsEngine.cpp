#include "PhysicsEngine.h"

PhysicsEngine::PhysicsEngine(RenderWindow * window, GraphicsEngine * graphics) : m_window(window), m_graphics(graphics)
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

void PhysicsEngine::setCharacter()
{
	Sprite * tmp = m_graphics->getCharacterImage();
	m_character->setX(tmp->getGlobalBounds().left);
	m_character->setY(tmp->getGlobalBounds().top);
}

void PhysicsEngine::operateCharacter(int x, int y)
{
	m_character->move(x, y);
	m_graphics->moveCharacter(m_character->getX(), m_character->getY());
}

bool PhysicsEngine::initEngine()
{
	switch (m_currentState)
	{
	case GAME_PHYSICS:
		m_character = new Character();		

		if (!m_map->loadMap())
			return false;
		m_map->display();
		break;

	default:
		return false;
	}

	return true;
}

Character * PhysicsEngine::getCharacter()
{
	return m_character;
}

Map * PhysicsEngine::getMap()
{
	return m_map;
}
