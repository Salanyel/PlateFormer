#include "CharacterImage.h"


CharacterImage::CharacterImage()
{
}


CharacterImage::~CharacterImage()
{
}

int CharacterImage::getX()
{
	return m_x;
}

int CharacterImage::getY()
{
	return m_y;
}

void CharacterImage::setX(int x)
{
	m_x = x;
}

void CharacterImage::setY(int y)
{
	m_y = y;
}

void CharacterImage::move(int x, int y)
{
	m_x += x;
	m_y += y;
}