#include "Character.h"


Character::Character()
{
	m_orientation = 1;
	m_jump = 0;
	m_jumpMax = 200;
	m_stateMachine = new StateMachine_Character();
}

Character::~Character()
{
	delete(m_stateMachine);
}

void Character::setX(int x)
{
	m_x = x;
}

void Character::setY(int y)
{
	m_y = y;
}

void Character::setCenter()
{
	int width = CHARACTER_WIDTH;
	int height = CHARACTER_HEIGHT;
	m_center.x = m_x + width / 2;
	m_center.y = m_y + height / 2;
}

int Character::getX()
{
	return m_x;
}

int Character::getY()
{
	return m_y;
}

coordonnee Character::getCenter()
{
	return m_center;
}

void Character::move()
{
	switch (m_stateMachine->getIdCurrentState())
	{
	case RUN :
		m_x += m_orientation * MOVE_VELOCITY;
		break;

	case JUMP :
		m_yOrientation = -1;
		if (m_jump < m_jumpMax)
		{
			m_y -= JUMP_VELOCITY;
			m_jump += JUMP_VELOCITY;
		}

		if (m_jump >= m_jumpMax)
		{
			m_y += abs(m_jumpMax - m_jump);
			m_jump = m_jumpMax;
			m_stateMachine->changeState(FLY);
		}
		break;

	case FLY :
		m_yOrientation = 1;
		/*if (m_jump > 0)
		{
			m_y += FALL_VELOCITY;
			m_jump -= FALL_VELOCITY;
		}

		if (m_jump < 0)
		{
			m_y += m_jump;			
			m_jump = 0;
			m_stateMachine->changeState(LAND);
		}*/
		m_y += FALL_VELOCITY;
		break;


	case LAND :
		m_jump = 0;
		m_yOrientation = 0;
		break;

	default :
		break;
	}
	//cout << m_center.y << endl;
	//cout << m_yOrientation << endl;
	setCenter();
}

void Character::jumpControl()
{
	m_x += m_orientation * MOVE_VELOCITY;
}

void Character::processEvents(Event event)
{
	if (event.type == Event::KeyPressed && event.key.code == Keyboard::Escape || event.type == Event::KeyPressed && event.key.code == Keyboard::Up)
	{
		m_stateMachine->changeState(JUMP);
	}
}

void Character::processEvents()
{
	if (Keyboard::isKeyPressed(Keyboard::Right))
	{
		m_stateMachine->changeState(RUN);
		m_orientation = 1;
		if (m_stateMachine->getIdCurrentState() == JUMP || m_stateMachine->getIdCurrentState() == FLY)
		{
			jumpControl();
		}			
	}

	if (Keyboard::isKeyPressed(Keyboard::Left))
	{
		m_stateMachine->changeState(RUN);
		m_orientation = -1;		
		if (m_stateMachine->getIdCurrentState() == JUMP || m_stateMachine->getIdCurrentState() == FLY)
		{
			jumpControl();
		}
	}

	/*if (Keyboard::isKeyPressed(Keyboard::Space) || Keyboard::isKeyPressed(Keyboard::Up))
	{
		m_stateMachine->changeState(JUMP);
	}*/
}

StateMachine_Character * Character::getStateMachine()
{
	return m_stateMachine;
}

int Character::getOrientation()
{
	return m_orientation;
}

int Character::getYOrientation()
{
	return m_yOrientation;
}