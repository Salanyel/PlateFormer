#pragma once
#include "SFML\Graphics.hpp"
#include <iostream>
#include "StateMachine_Character.h"

using namespace std;
using namespace sf;

#define MOVE_VELOCITY 4;
#define JUMP_VELOCITY 6;
#define FALL_VELOCITY 6;

class Character
{
public:
	Character();
	~Character();
	
	void setX(int x);
	void setY(int y);
	int getX();
	int getY();
	void move();
	void jumpControl();
	void processEvents(Event event);
	void processEvents();
	StateMachine_Character * getStateMachine();
	int getOrientation();
	
protected :
	int m_x;
	int m_y;
	int m_orientation;
	int m_jump;
	int m_jumpMax;
	StateMachine_Character * m_stateMachine;
};