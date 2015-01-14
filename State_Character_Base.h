#pragma once
#include "Character.h"
//#include "StateMachine_Character.h"

enum CHARACTER_STATES
{
	STAND,
	RUN
};

class State_Character_Base
{
public:
	State_Character_Base(Character * character);
	~State_Character_Base();

	virtual bool changeStateAvailable(CHARACTER_STATES newState) = 0;
	virtual bool initState(Character * character) = 0;
	virtual bool clearState() = 0;
	virtual void operate() = 0;

protected :
	Character * m_character;
};