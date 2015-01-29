#include "PhysicsEngine.h"

PhysicsEngine::PhysicsEngine(RenderWindow * window, GraphicsEngine * graphics) : m_window(window), m_graphics(graphics)
{
	m_map = new Map("Assets/Maps/maps.xml");
	m_momentums = new vector < Momentum * >() ;
}

PhysicsEngine::~PhysicsEngine()
{
	delete(m_map);
	m_momentums->clear();
	delete(m_momentums);
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
	coordonnee center = m_character->getCenter();
	int xOrientation = m_character->getOrientation();
	int yOrientation = m_character->getYOrientation();
	int characterHeight = CHARACTER_HEIGHT;
	int characterWidth = CHARACTER_WIDTH;
	int correctX = 0;
	int correctY = 0;
	int it;
	Tile * tile;
	Tile * tileTop;
	Tile * tileBottom;

	//Collide on Y
	if (yOrientation != 0)
	{
		tile = m_map->getTile(center.x / 64, (center.y + (yOrientation * characterHeight / 2)) / 64);
		if (tile->isSolid())
		{
			if (yOrientation == 1)
			{
				correctY = (center.y + (yOrientation * characterHeight / 2)) - (center.y + (yOrientation * characterHeight / 2)) / 64 * 64;
			}
			else {
				m_character->getStateMachine()->changeState(FLY);
			}
		}
	}

	//Collide on X
	tile = m_map->getTile((center.x + (xOrientation * characterWidth / 2)) / 64, center.y / 64);
	if (tile->isSolid())
	{
		if (xOrientation == 1)
		{
			correctX = ((center.x + (xOrientation * characterWidth / 2)) / 64 * 64) + (-xOrientation * characterWidth);
		}
		else {
			correctX = ((center.x + (xOrientation * characterWidth / 2)) / 64 * 64) + (-xOrientation * characterWidth) - 1;
		}
	}

	if (correctY != 0)
		m_character->setY(center.y - characterHeight / 2 - correctY);

	if (correctX != 0)
		m_character->setX(correctX);

	m_character->setCenter();

	tile = m_map->getTile(center.x / 64, (center.y + characterHeight / 2) / 64);
	if (!tile->isSolid() && m_character->getStateMachine()->getIdCurrentState() != JUMP)
	{
		m_character->getStateMachine()->changeState(FLY);
	}
	else {
		m_character->getStateMachine()->changeState(LAND);
	}
}

	/*Tile * tile;
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
*/
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
	if (m_character->getChronoTrigger() == 1)
	{
		Momentum * momentum = new Momentum();
		if (! m_momentums->empty())
		{ 
			momentum = m_momentums->back();
			m_momentums->pop_back();

			m_character->setX(momentum->getX());
			m_character->setY(momentum->getY());
			m_character->setJump(momentum->getJump());
			m_character->setXOrientation(momentum->getXOrientation());
			m_character->setYOrientation(momentum->getYOrientation());
			m_character->getStateMachine()->forceChangeState(momentum->getState());
			m_character->setCenter();
			m_character->setChronoTrigger();
		}		
	}
	else
	{
		operateShadow();
		m_character->move();
		saveMomentum();
	}	

	m_graphics->syncCharacter(m_character->getX(), m_character->getY(), m_character->getStateMachine()->getIdCurrentState(), m_character->getOrientation());
}

void PhysicsEngine::operateShadow()
{
	switch (m_character->getShadowUse())
	{
	case 1: 
		m_shadowX = m_character->getX();
		m_shadowY = m_character->getY();
		m_graphics->createShadow(m_shadowX, m_shadowY, m_character->getOrientation());
		m_character->setShadowUse(2);

	default:
		break;
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

void PhysicsEngine::saveMomentum()
{
	Momentum * momentum;
	//Momentum(int yOrientation, int xOrientation, int jump, int x, int y, CHARACTER_STATES state);
	momentum = new Momentum(m_character->getYOrientation(),
		m_character->getOrientation(),
		m_character->getJump(),
		m_character->getCenter().x - CHARACTER_WIDTH / 2,
		m_character->getCenter().y - CHARACTER_HEIGHT / 2,
		m_character->getStateMachine()->getIdCurrentState());

	//momentum->display();

	m_momentums->push_back(momentum);
}