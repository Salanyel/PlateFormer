#include "Momentum.h"


Momentum::Momentum(int yOrientation, int xOrientation, int jump, int x, int y, CHARACTER_STATES state)
{
	m_shadowOrientation = 0;
	m_yOrientation = yOrientation;
	m_xOrientation = xOrientation;
	m_jump = jump;
	m_x = x;
	m_y = y;
	m_state = state;
}

Momentum::Momentum()
{
	m_shadowOrientation = 0;
}


Momentum::~Momentum()
{
}

int Momentum::getXOrientation()
{
	return m_xOrientation;
}

int Momentum::getYOrientation()
{
	return m_yOrientation;
}

int Momentum::getJump()
{
	return m_jump;
}

int Momentum::getX()
{
	return m_x;
}

int Momentum::getY()
{
	return m_y;
}

int Momentum::getShadowY()
{
	return m_shadowY;
}

int Momentum::getShadowX()
{
	return m_shadowX;
}

int Momentum::getShadowOrientation()
{
	return m_shadowOrientation;
}

void Momentum::setShadowX(int x)
{
	m_shadowX = x;
}

void Momentum::setShadowY(int y)
{
	m_shadowY = y;
}

void Momentum::setShadowOrientation(int orientation)
{
	m_shadowOrientation = orientation;
}

void Momentum::display()
{
	cout << m_x << "(" << m_xOrientation << ")*" << m_y << "(" << m_yOrientation <<")" << endl;
	cout << "Jump :" << m_jump << endl;
	cout << "State : " << m_state << endl << endl;
}

CHARACTER_STATES Momentum::getState()
{
	return m_state;
}