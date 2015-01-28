#pragma once
#include "SFML\Graphics.hpp"
#include <iostream>
#include "StateMachine_Character.h"

using namespace std;
using namespace sf;

#define MOVE_VELOCITY 4
#define JUMP_VELOCITY 10
#define FALL_VELOCITY 13
#define CHARACTER_WIDTH 48
#define CHARACTER_HEIGHT 64

struct coordonnee
{
	int x;
	int y;
};

class Character
{
public:
	Character();
	~Character();
	
	void setX(int x);
	void setY(int y);
	void setCenter();
	void setChronoTrigger();
	void setJump(int jump);
	void setXOrientation(int xOrientation);
	void setYOrientation(int yOrientation);
	int getX();
	int getY();
	int getChronoTrigger();
	int getJump();
	coordonnee getCenter();
	void move();
	void jumpControl();
	void processEvents(Event event);
	void processEvents();
	StateMachine_Character * getStateMachine();
	int getOrientation();
	int getYOrientation();
	
protected :
	int m_x;
	int m_y;
	int m_orientation;
	int m_yOrientation;
	int m_jump;
	int m_jumpMax;
	int m_chronoTrigger;
	coordonnee m_center;
	StateMachine_Character * m_stateMachine;
};