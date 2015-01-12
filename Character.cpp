#include "Character.h"


Character::Character()
{
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

CharacterImage * Character::getCharacterImage()
{
	return m_image;
}

void Character::move(int x, int y)
{
	if (x == -1)
		m_x += -MOVE_VELOCITY;
	
	if (x == 1)
		m_x += MOVE_VELOCITY;

	if (y == -1)
		m_y += -JUMP_VELOCITY;

	if (y == 1)
		m_y += JUMP_VELOCITY;
}