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
	m_character->setCenter();
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

bool PhysicsEngine::collide()
{
	//TODO : Revoir l'algo de collision
	//Prioriser y
	//Puis X
	//Essayer de faire une méthode générale
	coordonnee center = m_character->getCenter();
	int xOrientation = m_character->getOrientation();
	int yOrientation;
	int characterHeight = CHARACTER_HEIGHT;
	int characterWidth = CHARACTER_WIDTH;
	Tile * tileUnder = m_map->getTile(center.x / 64, (center.y + characterHeight/2) / 64);

	if (tileUnder->isSolid())
	{
		m_character->getStateMachine()->changeState(LAND);
		correct();
	}

	//xCorrection
	int xToUsed = center.x + xOrientation * characterWidth;
	Tile * tileX = m_map->getTile(xToUsed / 64, center.y / 64);

	if (tileX->isSolid())
	{
		m_character->getStateMachine()->changeState(STAND);
		correct();
	}

	return false;
}

bool PhysicsEngine::fall()
{
	coordonnee center = m_character->getCenter();
	int xOrientation = m_character->getOrientation();
	int yOrientation;
	int characterHeight = CHARACTER_HEIGHT;
	Tile * tile = m_map->getTile(center.x / 64, center.y / 64 + 1);

	if (!tile->isSolid() && m_character->getStateMachine()->getIdCurrentState() != FLY && m_character->getStateMachine()->getIdCurrentState() != JUMP)
	{
		m_character->getStateMachine()->changeState(FLY);
		return true;
	}

	return false;
}

void PhysicsEngine::correct()
{
	Tile * tile;
	int xCharacter = m_character->getCenter().x;
	int yCharacter = m_character->getCenter().y;
	int xOrientation = m_character->getOrientation();
	int yOrientation = m_character->getYOrientation();
	int characterHeight = CHARACTER_HEIGHT;
	int characterWidth = CHARACTER_WIDTH;

	while (1)
	{		
		if (yOrientation != 0)
		{
			tile = m_map->getTile(xCharacter / 64, (yCharacter + characterHeight/2) / 64);
			if (tile->isSolid())
			{
				yCharacter += - yOrientation;
			}
			else
			{
				m_character->setY(yCharacter - characterHeight/2);
				m_character->setCenter();
				return;
			}
		}
		//TODO : bypass des lois physiques par le if else
		else
		{
			int xToUsed = xCharacter + xOrientation*characterWidth;

			cout << xToUsed << "/" << xCharacter << endl;			
			tile = m_map->getTile(xToUsed / 64, yCharacter / 64);
			if (tile->isSolid())
			{
				xToUsed += -xOrientation;
			}
			else
			{
				m_character->setX(xToUsed - characterWidth / 2);
				m_character->setCenter();
				return;
			}
		}
	}
}

void PhysicsEngine::simulate()
{
	if (!collide())
	{
		fall();
		m_character->move();
		m_graphics->syncCharacter(m_character->getX(), m_character->getY(), m_character->getStateMachine()->getIdCurrentState(), m_character->getOrientation());
	}
}

Character * PhysicsEngine::getCharacter()
{
	return m_character;
}

Map * PhysicsEngine::getMap()
{
	return m_map;
}
