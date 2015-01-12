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
	m_characters.at(0)->setX(tmp->getGlobalBounds().left);
	m_characters.at(0)->setY(tmp->getGlobalBounds().top);
}

void PhysicsEngine::operateCharacter(int x, int y)
{
	Character * character = m_characters.at(0);
	character->move(x, y);
	m_graphics->moveCharacter(character->getX(), character->getY());
}

bool PhysicsEngine::initEngine()
{
	switch (m_currentState)
	{
	case GAME_PHYSICS:
		Character * player;
		player = new Character();
		m_characters.push_back(player);

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
