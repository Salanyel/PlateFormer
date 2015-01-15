#include "Character.h"


Character::Character()
{
	m_orientation = 1;
	m_jump = 0;
	m_stateMachine = new StateMachine_Character();
}

Character::~Character()
{
}

void Character::setX(int x)
{
	m_x = x;
}

void Character::setY(int y)
{
	m_y = y;
}

int Character::getX()
{
	return m_x;
}

int Character::getY()
{
	return m_y;
}

void Character::move()
{
	switch (m_stateMachine->getIdCurrentState())
	{
	case CHARACTER_STATES::RUN :
		m_x += m_orientation * MOVE_VELOCITY;
		break;

	default :
		break;
	}
}

void Character::processEvents(Event event)
{
	/*if (event.type == Event::KeyPressed && event.key.code == Keyboard::Space)
	{
		m_stateMachine->changeState(CHARACTER_STATES::JUMP);
	}*/
}

void Character::processEvents()
{
	if (Keyboard::isKeyPressed(Keyboard::Right))
	{
		m_stateMachine->changeState(CHARACTER_STATES::RUN);
		m_orientation = 1;
	}

	if (Keyboard::isKeyPressed(Keyboard::Left))
	{
		m_stateMachine->changeState(CHARACTER_STATES::RUN);
		m_orientation = -1;		
	}

	if (Keyboard::isKeyPressed(Keyboard::Space))
	{
		m_stateMachine->changeState(CHARACTER_STATES::JUMP);
	}
}

StateMachine_Character * Character::getStateMachine()
{
	return m_stateMachine;
}

int Character::getOrientation()
{
	return m_orientation;
}