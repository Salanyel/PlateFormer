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

void PhysicsEngine::collide()
{
	Tile * tile;
	coordonnee center = m_character->getCenter();
	int correctX = 0;
	int correctY = 0;

	//Collide on Y
	if (m_character->getYOrientation() != 0)
	{
		correctY = collideY();
		if (correctY != 0)
		{
			m_character->setY(center.y - CHARACTER_HEIGHT / 2 - correctY);
		}			

		m_character->setCenter();
	}			

	//Collide on X
	if (correctY == 0)
	{
		correctX = collideX();
		if (correctX != 0)
			m_character->setX(correctX);
		m_character->setCenter();
	}
	
	//Test if the character is falling
	fallingTest();
}

int PhysicsEngine::collideY()
{
	Tile * tile;
	int newPosition = 0;
	int yOrientation = m_character->getYOrientation();
	coordonnee center = m_character->getCenter();
	
	for (int it = - CHARACTER_WIDTH / 2; it < CHARACTER_WIDTH / 2; ++it)
	{
		tile = m_map->getTile((center.x + it) / 64, (center.y + (yOrientation * CHARACTER_HEIGHT / 2)) / 64);
		if (tile->isSolid())
		{
			if (yOrientation == 1)
			{
				newPosition = (center.y + (yOrientation * CHARACTER_HEIGHT / 2)) - (center.y + (yOrientation * CHARACTER_HEIGHT / 2)) / 64 * 64;
				return newPosition;
			}
			else
			{
				newPosition = (center.y + (yOrientation * CHARACTER_HEIGHT / 2)) - ((center.y + (yOrientation * CHARACTER_HEIGHT / 2)) / 64 + 1) * 64;
				m_character->getStateMachine()->changeState(FLY);
				return newPosition;
			}				
		}
	}	
	return 0;
}

int PhysicsEngine::collideX()
{
	//TODO : correct the algo
	Tile * tile;
	int correct = 0;
	coordonnee center = m_character->getCenter();
	int xOrientation = m_character->getOrientation();

	for (int it = -CHARACTER_HEIGHT / 2; it < CHARACTER_HEIGHT / 2; ++it)
	{
		tile = m_map->getTile((center.x + (xOrientation * CHARACTER_WIDTH / 2)) / 64, (center.y + it) / 64);
		if (tile->isSolid())
		{
			if (xOrientation == 1)
			{
				cout << "Right collide detected." << endl;				
				correct = ((center.x + (xOrientation * CHARACTER_WIDTH / 2)) / 64 * 64);
				cout << "Emplacement tile : " << correct;
				correct = correct + (-xOrientation * CHARACTER_WIDTH);
				cout << " -- Correct : " << correct << endl << endl;
				m_character->getStateMachine()->changeState(STAND);
				/*correct = ((center.x + (xOrientation * CHARACTER_WIDTH / 2)) / 64 * 64) + (-xOrientation * CHARACTER_WIDTH);
				cout << center.x << "(" << correct << ")" << endl << endl;
				return correct;*/
				return correct;
			}
			else
			{
				cout << "Left collide detected." << endl;
				correct = ((center.x + (xOrientation * CHARACTER_WIDTH / 2)) / 64 * 64);
				cout << "Emplacement tile : " << correct;
				correct = correct + 64;
				cout << " -- Correct : " << correct << endl << endl;
				m_character->getStateMachine()->changeState(STAND);
				/*correct = ((center.x + (xOrientation * CHARACTER_WIDTH / 2)) / 64 * 64) + (-xOrientation * CHARACTER_WIDTH);
				cout << center.x << "(" << correct << ")" << endl << endl;
				return correct;*/
				return correct;
			}
		}
	}
	return 0;
}

void PhysicsEngine::fallingTest()
{
	Tile * tile;
	coordonnee center = m_character->getCenter();
	int it;

	for (it = -CHARACTER_WIDTH / 2; it < CHARACTER_WIDTH / 2; ++it)
	{
		tile = m_map->getTile((center.x + it) / 64, (center.y + CHARACTER_HEIGHT / 2) / 64);
		if (!tile->isSolid() && m_character->getStateMachine()->getIdCurrentState() != JUMP)
		{
			m_character->getStateMachine()->changeState(FLY);
		}
		else
		{
			m_character->getStateMachine()->changeState(LAND);
			return;
		}
	}	
}

/*void PhysicsEngine::correct()
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
}*/

void PhysicsEngine::simulate()
{
	collide();	
	m_character->move();
	m_graphics->syncCharacter(m_character->getX(), m_character->getY(), m_character->getStateMachine()->getIdCurrentState(), m_character->getOrientation());
}

Character * PhysicsEngine::getCharacter()
{
	return m_character;
}

Map * PhysicsEngine::getMap()
{
	return m_map;
}
