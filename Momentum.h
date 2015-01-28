#pragma once
#include "Character.h"

class Momentum
{
public:
	Momentum();
	Momentum(int yOrientation, int xOrientation, int jump, int x, int y, CHARACTER_STATES state);
	~Momentum();
	int getXOrientation();
	int getYOrientation();
	int getJump();
	int getX();
	int getY();
	void display();
	CHARACTER_STATES getState();

private :
	int m_yOrientation;
	int m_xOrientation;
	int m_jump;
	int m_x;
	int m_y;
	CHARACTER_STATES m_state;
};

